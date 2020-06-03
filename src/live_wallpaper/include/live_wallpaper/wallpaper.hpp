#pragma once
#include <list>

namespace live_wallpaper
{
	class wallpaper
	{
	public:
		wallpaper() = default;
		wallpaper(std::string name, std::list<std::string> frames, bool dubl_first_frame, uint64_t frame_delay,
		          uint64_t delay);

	private:
		std::string name_;
		std::list<std::string> frames_{};
		bool dubl_first_frame_{false};
		uint64_t frame_delay_{0};
		uint64_t delay_{0};
	};
}
