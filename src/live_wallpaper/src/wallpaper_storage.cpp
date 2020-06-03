#include "include/live_wallpaper/wallpaper_storage.hpp"

#include <filesystem>

namespace fs = std::experimental::filesystem;

namespace live_wallpaper
{
	void wallpaper_storage::add_wallpaper(wallpaper const& wp)
	{
	}

	void wallpaper_storage::restore_wallpapers()
	{
		for(auto const& i : fs::directory_iterator(storage_folder_))
		{
			if(fs::is_directory(i.path()) && !fs::is_empty(i.path()))
			{
				wallpaper wp;
			}
		}
	}

	wallpaper wallpaper_storage::get_wallpaper(std::string const& name)
	{
		const auto wp = wallpapers_.find(name);
		if(wp != wallpapers_.end())
			return wp->second;

		return wallpaper();
	}
}
