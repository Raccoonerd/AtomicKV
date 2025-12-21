#include "../include/Logger.hpp"
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/console.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/sources/record_ostream.hpp>
#include <boost/log/support/date_time.hpp>
#include <boost/log/utility/manipulators/add_value.hpp>
#include <boost/log/attributes/value_extraction.hpp>


namespace logging = boost::log;
namespace keywords = boost::log::keywords;
namespace expr = boost::log::expressions;
namespace sinks = boost::log::sinks;

void init_logging(){
  logging::add_common_attributes();

  auto console_sink = logging::add_console_log(
    std::cout,
    keywords::format = (
      expr::stream
        << "[" << expr::format_date_time<boost::posix_time::ptime>("TimeStamp", "%Y-%m-%d %H:%M:%S") << "]"
        << "["<< logging::trivial::severity <<"]"
        << expr::message
    )
  );

  logging::add_file_log(
    keywords::file_name = "AtomicKV_%Y%m%d-%H%M%S.log",
    keywords::rotation_size = 10 * 1024 * 1024,
    keywords::time_based_rotation = logging::sinks::file::rotation_at_time_point(0,0,0),
    keywords::format = (
      expr::stream
        << "[" << expr::format_date_time<boost::posix_time::ptime>("TimeStamp", "%Y-%m-%d %H:%M:%S") << "]"
        << "["<< logging::trivial::severity <<"]"
        << expr::message
    ),
    keywords::auto_flush = true
  );

  logging::core::get() -> set_filter(
    logging::trivial::severity >= logging::trivial::info
  );

  BOOST_LOG_TRIVIAL(info) << "Looing initialized succesfully";
}
