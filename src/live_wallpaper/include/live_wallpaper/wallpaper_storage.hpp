#pragma once
#include "include/live_wallpaper/wallpaper.hpp"

#include <map>

namespace live_wallpaper
{
	class wallpaper_storage
	{
	public:
		wallpaper_storage() = default;

		void add_wallpaper(wallpaper const& wp);
		void restore_wallpapers();
		wallpaper get_wallpaper(std::string const& name);

	private:
		std::map<std::string, wallpaper> wallpapers_;
		std::string storage_folder_{ "/.cache" };
	};
}