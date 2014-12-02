#ifndef LOG_H
#define LOG_H

#include <boost/log/trivial.hpp>
#include <boost/move/utility.hpp>
#include <boost/log/sources/logger.hpp>
#include <boost/log/sources/record_ostream.hpp>
#include <boost/log/sources/severity_feature.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/sources/global_logger_storage.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/sinks/sync_frontend.hpp>

enum severity_level {  debug,  info,  warning,  error,  critical};

BOOST_LOG_INLINE_GLOBAL_LOGGER_DEFAULT(my_logger,
  boost::log::sources::severity_logger_mt<severity_level>)

class Log {
  boost::shared_ptr
  <boost::log::v2_mt_posix::sinks::synchronous_sink
   <boost::log::v2_mt_posix::sinks::text_file_backend> > log_handler;

public:
  Log();
  void flush();
};


#endif
