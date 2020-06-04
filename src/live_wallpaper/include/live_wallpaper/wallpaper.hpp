#pragma once
#include <list>

namespace live_wallpaper
{
	class wallpaper
	{
	public:
		wallpaper() = default;
		wallpaper(std::string name, std::list<std::string> frames,
		          bool first_frame_duplication,
		          uint64_t frame_delay, uint64_t delay);

		std::string get_name() const;
		std::list<std::string> get_frames() const;
		bool get_duplication() const;
		uint64_t get_frame_delay() const;
		uint64_t get_delay() const;

	private:
		std::string name_;
		std::list<std::string> frames_{};
		bool first_frame_duplication_{false};
		uint64_t frame_delay_{0};
		uint64_t delay_{0};
	};
}
