#pragma once
#include "include/live_wallpaper/logger.hpp"
#include "include/live_wallpaper/wallpaper.hpp"

namespace live_wallpaper
{
	enum class wallpaper_style : int
	{
		center = 0,
		tile = 1,
		stretch = 2,
		keepaspect = 3,
		croptofit = 4,
		span = 5,
		max = 6
	};

	class live_wallpaper
	{
	public:
		live_wallpaper() = default;

		std::string https_get(std::string const& uri) const;

		void https_get_image(std::string const& host, std::string const& path) const;

		std::string get_image_location_from_html(std::string const& html_body) const;

		std::string get_image_from_cache(std::string const& wp) const;

		void write_file(std::string const& info) const;

		static void set_wallpapers_option(wallpaper_style style = wallpaper_style::keepaspect);

		void set_wallpaper(std::string const& path, wallpaper_style style = wallpaper_style::keepaspect);

		void slide_show(wallpaper const& wp);

		void start_slide_show(wallpaper const& wp);

		void start();
		void stop();

	private:
		bool wp_opts_set_{false};
		bool stop_slide_show_{false};
		static logger logger_;
	};
}
