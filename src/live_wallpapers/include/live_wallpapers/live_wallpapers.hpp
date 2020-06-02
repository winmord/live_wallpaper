#pragma once
#include <string>
#include <filesystem>

namespace live_wallpapers
{
	enum class wallpaper_style
	{
		WPSTYLE_CENTER,
		WPSTYLE_TILE,
		WPSTYLE_STRETCH,
		WPSTYLE_KEEPASPECT,
		WPSTYLE_CROPTOFIT,
		WPSTYLE_SPAN,
		WPSTYLE_MAX
	};

	class live_wallpapers
	{
	public:
		live_wallpapers() = default;

		std::string https_get(std::string const& uri);

		std::string get_image_from_html(std::string const& html_body);

		std::string get_image_from_cache(std::string const& wp);

		void set_wallpapers(std::string const& path);

		void write_file(std::string const& info);

		void slide_show(std::string const& path = ".cache", int const& delay = 0);

		void get_image(std::string const& host, std::string const& path);
	};
}