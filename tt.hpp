#ifndef __MYTINY_HPP__
#define __MYTINY_HPP__

#include <string>
#include "./iniparser.h"
#include "./log4cplus/logger.h"
#include "./log4cplus/loggingmacros.h"

extern log4cplus::Logger _logger;
int initLog(std::string name, std::string path);

#define log_fatal(logEvent)	LOG4CPLUS_FATAL(_logger, logEvent)
#define log_error(logEvent)	LOG4CPLUS_ERROR(_logger, logEvent)
#define log_warn(logEvent)	LOG4CPLUS_WARN(_logger, logEvent)
#define log_info(logEvent)	LOG4CPLUS_INFO(_logger, logEvent)
#define log_debug(logEvent)	LOG4CPLUS_DEBUG(_logger, logEvent)
#define log_trace(logEvent)	LOG4CPLUS_TRACE(_logger, logEvent)

#endif // __MYTINY_HPP__
