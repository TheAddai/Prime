#pragma once

#include "engine/platform/platform.h"

#include <spdlog/spdlog.h>

namespace prime {

	class Logger
	{
	public:
		static void Init();
		static void Shutdown();

		static std::shared_ptr<spdlog::logger>& Get();
	};

}

#ifdef PCONFIG_DEBUG
#define PTRACE(...)                 prime::Logger::Get()->trace(__VA_ARGS__)
#define PINFO(...)                  prime::Logger::Get()->info(__VA_ARGS__)
#define PWARN(...)                  prime::Logger::Get()->warn(__VA_ARGS__)
#define PERROR(...)                 prime::Logger::Get()->error(__VA_ARGS__)
#else
#define PTRACE(...)                 void()0
#define PINFO(...)                  void()0
#define PWARN(...)                  void()0
#define PERROR(...)                 void()0
#endif // PCONFIG_DEBUG