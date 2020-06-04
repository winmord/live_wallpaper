#include "include/live_wallpaper/wallpaper_storage.hpp"

#include <filesystem>
#include <fstream>
#include <nlohmann/json.hpp>
#include <algorithm>

namespace fs = std::experimental::filesystem;

namespace live_wallpaper
{
	wallpaper_storage::wallpaper_storage()
	{
		if (!fs::is_directory(storage_folder_))
		{
			fs::create_directory(storage_folder_);

			if (!fs::is_directory(jsons_folder_)) fs::create_directory(jsons_folder_);
			if (!fs::is_directory(srcs_folder_)) fs::create_directory(srcs_folder_);
		}
	}

	void wallpaper_storage::create_wallpaper(std::string const& name, std::string const& path_to_frames,
	                                         bool first_frame_duplication,
	                                         uint64_t frame_delay, uint64_t delay) const
	{
		if (fs::is_directory(path_to_frames) && !fs::is_empty(path_to_frames))
		{
			const auto folder = srcs_folder_ + "/" + name;
			fs::copy(path_to_frames, folder);
			auto frames = std::list<std::string>{};

			for (auto const& i : fs::directory_iterator(folder))
			{
				if (!fs::is_directory(i.path()))
				{
					auto path = fs::current_path().string() + "/" + i.path().string();
					std::replace(path.begin(), path.end(), '\\', '/');

					frames.push_back(path);
				}
			}

			if (frames.empty()) throw std::runtime_error("There isn't any frame");

			save_wallpaper(wallpaper(name, frames, first_frame_duplication, frame_delay, delay));
		}
		else
		{
			throw std::runtime_error("Invalid path to frames");
		}
	}

	wallpaper wallpaper_storage::load_wallpaper(std::string const& name) const
	{
		std::ifstream ifs(name);
		auto j = nlohmann::json::parse(ifs);

		return wallpaper(
							j["name"],
							j["frames"],
							j["duplication"],
							j["frame_delay"],
							j["delay"]
						);
	}

	void wallpaper_storage::save_wallpaper(wallpaper const& wp) const
	{
		nlohmann::json j;

		j["name"] = wp.get_name();
		j["frames"] = wp.get_frames();
		j["duplication"] = wp.get_duplication();
		j["frame_delay"] = wp.get_frame_delay();
		j["delay"] = wp.get_delay();

		std::ofstream of(jsons_folder_ + "/" + wp.get_name() + ".json");
		of << j;
		of.close();
	}

	void wallpaper_storage::restore_wallpapers()
	{
		for (auto const& i : fs::directory_iterator(jsons_folder_))
		{
			if (!fs::is_directory(i.path()))
			{
				const auto wp = load_wallpaper(i.path().string());
				auto lb = wallpapers_.lower_bound(wp.get_name());

				if (lb != wallpapers_.end() && !(wallpapers_.key_comp()(wp.get_name(), lb->first)))
				{
					lb->second = wp;
				}
				else
				{
					wallpapers_.insert(std::pair<std::string, wallpaper>(wp.get_name(), wp));
				}
			}
		}
	}

	wallpaper wallpaper_storage::get_wallpaper(std::string const& name)
	{
		const auto wp = wallpapers_.find(name);

		if (wp != wallpapers_.end())
		{
			return wp->second;
		}

		return wallpaper();
	}
}
