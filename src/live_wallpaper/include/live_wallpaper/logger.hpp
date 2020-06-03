#pragma once
#include <boost/log/trivial.hpp>
#include <boost/log/sources/severity_logger.hpp>

namespace live_wallpaper
{
	class logger
	{
	public:
		logger();

		void log_info(std::string const& info);
		void log_warning(std::string const& warning);
		void log_error(std::string const& error);

	private:
		void init() const;

		boost::log::sources::severity_logger<boost::log::trivial::severity_level> logger_;
	};
}