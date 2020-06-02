#include "include\live_wallpapers\live_wallpapers.hpp"

#include <Poco/Hash.h>
#include <Poco/Net/HTTPClientSession.h>
#include <Poco/Net/HTTPRequest.h>
#include <Poco/Net/HTTPResponse.h>
#include <Poco/Net/HTTPSClientSession.h>
#include <Poco/StreamCopier.h>
#include <Poco/Path.h>
#include <Poco/URI.h>
#include <Poco/Exception.h>
#include <iostream>
#include <sstream>
#include <regex>
#include <WinSock2.h>
#include <Windows.h>
#include <wininet.h>
#include <ShlObj.h>
#include <fstream>
#include <streambuf>
#include <fstream>
#include <vector>
#include <thread>

using namespace Poco;
using namespace Poco::Net;

namespace live_wallpapers
{
	std::string live_wallpapers::https_get(std::string const& uri)
	{
		URI inner_uri(uri);
		HTTPSClientSession session(inner_uri.getHost(), inner_uri.getPort());

		std::string path(inner_uri.getPathAndQuery());
		if (path.empty()) path = "/";

		HTTPRequest req(HTTPRequest::HTTP_GET, path, HTTPMessage::HTTP_1_1);
		session.sendRequest(req);

		HTTPResponse res;
		std::cout << res.getStatus() << " " << res.getReason() << std::endl;

		if (res.getStatus() == 200)
		{
			std::stringstream ss;
			std::istream &is = session.receiveResponse(res);
			StreamCopier::copyStream(is, ss);

			return std::string(ss.str());
		}

		return std::string();
	}

	std::string live_wallpapers::get_image_from_html(std::string const & html_body)
	{
		std::regex re("IMG SRC=\".*?\"");
		std::smatch match;
		regex_search(html_body, match, re);

		if (!match.empty())
		{
			auto matched_str = match.str();
			auto image_location = std::string(matched_str.begin() + matched_str.find("\"") + 1,
											  matched_str.end() - matched_str.size() + matched_str.rfind("\"")
											 );
			return image_location;
		}

		return std::string();
	}
	std::string live_wallpapers::get_image_from_cache(std::string const & wp)
	{
		return std::string(std::experimental::filesystem::current_path().string() + 
								"/.cache/" + std::to_string(Poco::hash(wp)) + ".jpeg");
	}

	void live_wallpapers::set_wallpapers(std::string const & path)
	{
		CoInitialize(0);
		IActiveDesktop* pIActiveDesktop = NULL;
		HRESULT hr = CoCreateInstance(CLSID_ActiveDesktop, NULL, CLSCTX_INPROC_SERVER, IID_IActiveDesktop, (void**)&pIActiveDesktop);

		if (SUCCEEDED(hr))
		{
			WALLPAPEROPT s_info;
			s_info.dwSize = sizeof(WALLPAPEROPT);
			s_info.dwStyle = WPSTYLE_CENTER;
			
			/*

			WPSTYLE_CENTER
			WPSTYLE_TILE
			WPSTYLE_STRETCH
			WPSTYLE_KEEPASPECT
			WPSTYLE_CROPTOFIT
			WPSTYLE_SPAN
			WPSTYLE_MAX
			
			*/

			hr = pIActiveDesktop->SetWallpaperOptions(&s_info, 0);
			
			if (SUCCEEDED(hr))
			{
				pIActiveDesktop->ApplyChanges(AD_APPLY_ALL);
			}

			SystemParametersInfo(SPI_SETDESKWALLPAPER, 0, (PVOID)(path.c_str()), SPIF_UPDATEINIFILE | SPIF_SENDCHANGE);
		}
	}

	void live_wallpapers::write_file(std::string const& info)
	{
		if (!std::experimental::filesystem::is_directory(".cache"))
		{
			std::experimental::filesystem::create_directory(".cache");
		}

		std::string wp{ ".cache/" + std::to_string(Poco::hash(info)) + ".jpeg" };
		std::ofstream of(wp, std::ios::binary);
		of << info;
		of.close();
	}

	void live_wallpapers::slide_show(std::string const & path, int const& delay)
	{
		std::vector<std::string> photos{};
		for (auto const& i : std::experimental::filesystem::directory_iterator(path))
		{
			photos.push_back(i.path().string());
		}

		while (true)
		{
			for (auto const& i : photos)
			{
				set_wallpapers(i);
				std::this_thread::sleep_for(std::chrono::seconds(delay));
			}
		}
	}

	void live_wallpapers::get_image(std::string const & host, std::string const & path)
	{
		const auto html_body = https_get(host + path);
		const auto image_location = get_image_from_html(html_body);
		const auto image = https_get(host + "/" + image_location);

		write_file(image);
	}
}