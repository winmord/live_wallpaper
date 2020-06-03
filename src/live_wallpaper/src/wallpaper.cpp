#include <utility>
#include "include/live_wallpaper/wallpaper.hpp"

namespace live_wallpaper
{
	wallpaper::wallpaper(std::string name, std::list<std::string> frames,
	                     bool dubl_first_frame, const uint64_t frame_delay,
	                     const uint64_t delay)
		: name_(std::move(name)), frames_(std::move(frames)), dubl_first_frame_(dubl_first_frame),
		  frame_delay_(frame_delay), delay_(delay)
	{
	}
}
