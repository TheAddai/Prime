
#include "pch.h"
#include "logger.h"

#include <spdlog/sinks/stdout_color_sinks.h>

namespace prime {

	static std::shared_ptr<spdlog::logger> s_logger;

	void Logger::Init()
	{
		spdlog::set_pattern("%n: %v%$");
		s_logger = spdlog::stderr_color_mt("PRIME");
		s_logger->set_level(spdlog::level::trace);
	}

	void Logger::Shutdown()
	{
		spdlog::shutdown();
	}

	std::shared_ptr<spdlog::logger>& Logger::Get()
	{
		return s_logger;
	}
}