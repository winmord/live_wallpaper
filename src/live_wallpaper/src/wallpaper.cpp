#include <utility>
#include "include/live_wallpaper/wallpaper.hpp"

namespace live_wallpaper
{
	wallpaper::wallpaper(std::string name, std::list<std::string> frames,
	                     bool first_frame_duplication, const uint64_t frame_delay,
	                     const uint64_t delay)
		: name_(std::move(name)), frames_(std::move(frames)),
		  first_frame_duplication_(first_frame_duplication),
		  frame_delay_(frame_delay), delay_(delay)
	{
	}

	std::string wallpaper::get_name() const
	{
		return name_;
	}

	std::list<std::string> wallpaper::get_frames() const
	{
		return frames_;
	}

	bool wallpaper::get_duplication() const
	{
		return first_frame_duplication_;
	}

	uint64_t wallpaper::get_frame_delay() const
	{
		return frame_delay_;
	}

	uint64_t wallpaper::get_delay() const
	{
		return delay_;
	}
}
