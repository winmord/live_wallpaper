#include "include/live_wallpaper/logger.hpp"

#include <boost/log/core.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/sinks/text_file_backend.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/support/date_time.hpp>

namespace live_wallpaper
{
	logger::logger()
	{
		init();
		boost::log::add_common_attributes();
		logger_ = boost::log::sources::severity_logger<boost::log::trivial::severity_level>();
	}

	void logger::init() const
	{
		boost::log::add_file_log
		(
			boost::log::keywords::file_name = "logs/sample_%N.log",
			boost::log::keywords::format =
			(
				boost::log::expressions::stream
				<< "[" << boost::log::expressions::format_date_time<boost::posix_time::ptime>(
					"TimeStamp", "%Y-%m-%d %H:%M:%S")
				<< " " << boost::log::trivial::severity
				<< "] " << boost::log::expressions::smessage
			)
		);

		boost::log::core::get()->set_filter
		(
			boost::log::trivial::severity >= boost::log::trivial::info
		);
	}

	void logger::log_info(std::string const& info)
	{
		BOOST_LOG_SEV(logger_, boost::log::trivial::info) << info;
	}

	void logger::log_warning(std::string const& warning)
	{
		BOOST_LOG_SEV(logger_, boost::log::trivial::warning) << warning;
	}

	void logger::log_error(std::string const& error)
	{
		BOOST_LOG_SEV(logger_, boost::log::trivial::error) << error;
	}
}
