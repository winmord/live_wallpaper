#pragma once
#include "include/live_wallpaper/wallpaper.hpp"

#include <map>

namespace live_wallpaper
{
	class wallpaper_storage
	{
	public:
		wallpaper_storage();

		void create_wallpaper(std::string const& name, std::string const& path_to_frames,
		                      bool first_frame_duplication_,
		                      uint64_t frame_delay, uint64_t delay) const;

		wallpaper load_wallpaper(std::string const& name) const;

		void save_wallpaper(wallpaper const& wp) const;

		void restore_wallpapers();

		wallpaper get_wallpaper(std::string const& name);

	private:
		std::map<std::string, wallpaper> wallpapers_;
		std::string storage_folder_{".cache"};
		std::string jsons_folder_{storage_folder_ + "/jsons"};
		std::string srcs_folder_{storage_folder_ + "/srcs"};
	};
}
