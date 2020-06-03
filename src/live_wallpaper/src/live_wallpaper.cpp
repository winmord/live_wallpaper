#include "include/live_wallpaper/live_wallpaper.hpp"

#include <Poco/Hash.h>
#include <Poco/Net/HTTPClientSession.h>
#include <Poco/Net/HTTPRequest.h>
#include <Poco/Net/HTTPResponse.h>
#include <Poco/Net/HTTPSClientSession.h>
#include <Poco/StreamCopier.h>
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
#include <experimental/filesystem>
#include <vector>
#include <thread>

using namespace Poco;
using namespace Net;
namespace fs = std::experimental::filesystem;

namespace live_wallpaper
{
	logger live_wallpaper::logger_ = logger();

	std::string live_wallpaper::https_get(std::string const& uri) const
	{
		URI inner_uri(uri);
		HTTPSClientSession session(inner_uri.getHost(), inner_uri.getPort());

		auto path(inner_uri.getPathAndQuery());
		if (path.empty()) path = "/";

		HTTPRequest req(HTTPRequest::HTTP_GET, path, HTTPMessage::HTTP_1_1);
		session.sendRequest(req);

		HTTPResponse res;
		std::cout << res.getStatus() << " " << res.getReason() << std::endl;

		if (res.getStatus() == 200)
		{
			std::stringstream ss;
			auto& is = session.receiveResponse(res);
			StreamCopier::copyStream(is, ss);

			return std::string(ss.str());
		}

		logger_.log_warning("Status is: " + std::to_string(res.getStatus()));

		return std::string();
	}

	std::string live_wallpaper::get_image_location_from_html(std::string const& html_body) const
	{
		const std::regex re("IMG SRC=\".*?\"");
		std::smatch match;
		regex_search(html_body, match, re);

		if (!match.empty())
		{
			auto matched_str = match.str();
			auto image_location = std::string(matched_str.begin() +
			                                  matched_str.find('\"') + 1,
			                                  matched_str.end() -
			                                  matched_str.size() +
			                                  matched_str.rfind('\"')
			);
			return image_location;
		}

		logger_.log_warning("Match is empty");
		return std::string();
	}

	std::string live_wallpaper::get_image_from_cache(std::string const& wp) const
	{
		return std::string(fs::current_path().string() +
			"/.cache/" + std::to_string(hash(wp)) + ".jpeg");
	}

	void live_wallpaper::set_wallpapers_option(wallpaper_style style)
	{
		CoInitialize(nullptr);
		IActiveDesktop* p_i_active_desktop = nullptr;
		auto hr = CoCreateInstance(CLSID_ActiveDesktop, nullptr,
		                           CLSCTX_INPROC_SERVER,
		                           IID_IActiveDesktop,
		                           reinterpret_cast<void**>(&p_i_active_desktop));

		if (SUCCEEDED(hr))
		{
			WALLPAPEROPT s_info;
			s_info.dwSize = sizeof(WALLPAPEROPT);
			s_info.dwStyle = static_cast<DWORD>(style);

			hr = p_i_active_desktop->SetWallpaperOptions(&s_info, 0);

			if (SUCCEEDED(hr))
			{
				p_i_active_desktop->ApplyChanges(AD_APPLY_ALL);
			}
		}
		else
		{
			logger_.log_warning("Ad applying failed");
		}
	}

	void live_wallpaper::set_wallpaper(std::string const& path, wallpaper_style style)
	{
		if (!this->wp_opts_set_)
		{
			set_wallpapers_option(style);
			wp_opts_set_ = true;
		}

		SystemParametersInfo(SPI_SETDESKWALLPAPER, 0, PVOID(path.c_str()),
		                     SPIF_UPDATEINIFILE | SPIF_SENDCHANGE);
	}

	void live_wallpaper::write_file(std::string const& info) const
	{
		if (!fs::is_directory(".cache"))
		{
			fs::create_directory(".cache");
		}

		const auto wp{".cache/" + std::to_string(hash(info)) + ".jpeg"};
		std::ofstream of(wp, std::ios::binary);
		of << info;
		of.close();
	}

	void live_wallpaper::slide_show(std::string const& path, int const& frames_delay, int const& delay)
	{
		std::list<std::string> photos{};
		for (auto const& i : fs::directory_iterator(path))
		{
			photos.push_back(i.path().string());
		}

		if (!photos.empty())
		{
			while (true)
			{
				for (auto const& i : photos)
				{
					set_wallpaper(i, wallpaper_style::stretch);
					std::this_thread::sleep_for(std::chrono::seconds(frames_delay));
				}

				std::this_thread::sleep_for(std::chrono::seconds(delay));
			}
		}

		logger_.log_warning("Empty slide show");
	}

	void live_wallpaper::https_get_image(std::string const& host, std::string const& path) const
	{
		const auto html_body = https_get(host + path);
		const auto image_location = get_image_location_from_html(html_body);
		const auto image = https_get(host + "/" + image_location);

		if (!image.empty())
		{
			write_file(image);
		}
		else
		{
			logger_.log_warning("There is no image");
		}
	}
}
