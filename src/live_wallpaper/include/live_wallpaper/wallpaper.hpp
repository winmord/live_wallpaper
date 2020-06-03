#pragma once
#include <list>

namespace live_wallpaper
{
	class wallpaper
	{
	public:
		wallpaper() = default;

		void add_wallpapers_from_cache();

	private:
		std::list<std::string> frames_{};
		bool dubl_first_frame_{false};
		uint64_t frame_delay_{ 0 };
		uint64_t delay_{ 0 };
	};
}
