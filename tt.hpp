#ifndef __TT_HPP__
#define __TT_HPP__

#include <iostream>
#include <memory>
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/sinks/basic_file_sink.h"
#include "INIReader.h"

std::shared_ptr<spdlog::logger> tt_logger;

int initLog(std::string name, std::string path = "")
{
    std::cout << "start initLog..." << std::endl;

    spdlog::level::level_enum lvl = spdlog::level::trace;
    if (path == "") {
	std::cout << "default log." << std::endl;
	lvl = spdlog::level::info;
    } else {
	INIReader reader(path);
	if (reader.ParseError() != 0) {
	    std::cout << "Can't load ini file: " << path << std::endl;
	    return -1;
	}
	std::string s = reader.Get("LOG", "level", "info");
	if ("critical" == s) {
	    lvl = spdlog::level::critical;
	} else if ("error" == s) {
	    lvl = spdlog::level::err;
	} else if ("warn" == s) {
	    lvl = spdlog::level::warn;
	} else if ("info" == s) {
	    lvl = spdlog::level::info;
	} else if ("debug" == s) {
	    lvl = spdlog::level::debug;
	} else if ("trace" == s) {
	    lvl = spdlog::level::trace;
	} else {
	    lvl = spdlog::level::info;
	    std::cout << "parse log level failed! default level is info.";
	}
    }

    try
    {
	auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
	console_sink->set_level(lvl);
	console_sink->set_pattern("[%Y-%m-%d %H:%M:%S.%e][%@][%l] - %v");

	auto file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>("../log/log.txt", true);
	file_sink->set_level(lvl);
	file_sink->set_pattern("[%Y-%m-%d %H:%M:%S.%e][%@][%l] - %v");

	spdlog::logger logger(name.c_str(), { console_sink, file_sink });
	logger.set_level(lvl);
	tt_logger = std::make_shared<spdlog::logger>(logger);
    }
    catch (const spdlog::spdlog_ex& ex)
    {
	std::cout << "Log initialization failed: " << ex.what() << std::endl;
    }

    return 0;
}

#define tt_trace(...) SPDLOG_LOGGER_CALL((tt_logger), spdlog::level::trace, __VA_ARGS__)
#define tt_debug(...) SPDLOG_LOGGER_CALL((tt_logger), spdlog::level::debug, __VA_ARGS__)
#define tt_info(...) SPDLOG_LOGGER_CALL((tt_logger), spdlog::level::info, __VA_ARGS__)
#define tt_warn(...) SPDLOG_LOGGER_CALL((tt_logger), spdlog::level::warn, __VA_ARGS__)
#define tt_error(...) SPDLOG_LOGGER_CALL((tt_logger), spdlog::level::error, __VA_ARGS__)
#define tt_critical(...) SPDLOG_LOGGER_CALL((tt_logger), spdlog::level::critical, __VA_ARGS__)

#endif // __TT_HPP__
