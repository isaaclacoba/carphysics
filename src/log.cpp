// -*- coding:utf-8; tab-width:4; mode:cpp -*-
#include "log.h"

namespace logging = boost::log;
namespace src = boost::log::sources;
namespace keywords = boost::log::keywords;

Log::Log() {
  log_handler = logging::add_file_log("config/game.log");

  logging::add_common_attributes();
}

void
Log::flush() {
  log_handler->flush();
}
