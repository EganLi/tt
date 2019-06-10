#include <iostream>
#include <string.h>
#include <string>
#include "../include/tt.hpp"
#include "../include/log4cplus/consoleappender.h"
#include "../include/log4cplus/fileappender.h"
#include "../include/log4cplus/layout.h"

log4cplus::Logger _logger;

int initLog(std::string name, std::string path)
{
	std::cout << "start initLog..." << std::endl;
	dictionary *ini = iniparser_load(path.c_str());
	if (NULL == ini)
	{
		std::cout << "initLog, failed to parse ini." << std::endl;
		return -1;
	}
	const char *s = iniparser_getstring(ini, "log:level", "info");

	_logger = log4cplus::Logger::getInstance(name);
	if (!strcmp(s, "fatal"))
	{
		_logger.setLogLevel(log4cplus::FATAL_LOG_LEVEL);
	}
	else if (!strcmp(s, "error"))
	{
		_logger.setLogLevel(log4cplus::ERROR_LOG_LEVEL);
	}
	else if (!strcmp(s, "warn"))
	{
		_logger.setLogLevel(log4cplus::WARN_LOG_LEVEL);
	}
	else if (!strcmp(s, "info"))
	{
		_logger.setLogLevel(log4cplus::INFO_LOG_LEVEL);
	}
	else if (!strcmp(s, "debug"))
	{
		_logger.setLogLevel(log4cplus::DEBUG_LOG_LEVEL);
	}
	else if (!strcmp(s, "trace"))
	{
		_logger.setLogLevel(log4cplus::TRACE_LOG_LEVEL);
	}
	else
	{
		std::cout << "Have a error when set log level!" << std::endl;
		return -2;
	}

	s = iniparser_getstring(ini, "log:output", "console");
	std::string str_appenders(s);
	if (std::string::npos != str_appenders.find("console"))
	{
		log4cplus::SharedAppenderPtr console_appender(new log4cplus::ConsoleAppender());
		console_appender->setName("console");
		const char *c_console = iniparser_getstring(ini, "console:pattern", "[%D{%Y-%m-%d %H:%M:%S}][%l] - %m%n");
		std::auto_ptr<log4cplus::Layout> console_layout(new log4cplus::PatternLayout(c_console));
		console_appender->setLayout(console_layout);
		_logger.addAppender(console_appender);
	}

	if (std::string::npos != str_appenders.find("file"))
	{
		const char *c_file_name = iniparser_getstring(ini, "file:filename", name.c_str());
		const char *c_file_schedule = iniparser_getstring(ini, "file:schedule", "daily");
		log4cplus::DailyRollingFileSchedule e_schedule = log4cplus::DAILY;
		if (!strcmp(c_file_schedule, "monthly"))
		{
			e_schedule = log4cplus::MONTHLY;
		}
		else if (!strcmp(c_file_schedule, "weekly"))
		{
			e_schedule = log4cplus::WEEKLY;
		}
		else if (!strcmp(c_file_schedule, "daily"))
		{
			e_schedule = log4cplus::DAILY;
		}
		else if (!strcmp(c_file_schedule, "hourly"))
		{
			e_schedule = log4cplus::HOURLY;
		}
		else if (!strcmp(c_file_schedule, "minutely"))
		{
			e_schedule = log4cplus::MINUTELY;
		}
		else
		{
			std::cout << "Have a error when set file schedule!" << std::endl;
			return -3;
		}
		int i_file_maxbackupindex = iniparser_getint(ini, "file:maxbackupindex", 10);
		log4cplus::SharedAppenderPtr file_appender(new log4cplus::DailyRollingFileAppender(c_file_name, e_schedule, true, i_file_maxbackupindex));
		file_appender->setName("file");
		const char *c_file_pattern = iniparser_getstring(ini, "file:pattern", "[%D{%Y-%m-%d %H:%M:%S}][%l] - %m%n");
		std::auto_ptr<log4cplus::Layout> file_layout(new log4cplus::PatternLayout(c_file_pattern));
		file_appender->setLayout(file_layout);
		_logger.addAppender(file_appender);
	}
}
