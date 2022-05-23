#pragma once

#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace Brio
{
	class Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};
}

// Core log macros
#define BR_CORE_ERROR(...)  ::Brio::Log::GetCoreLogger()->error(__VA_ARGS__)
#define BR_CORE_WARN(...)   ::Brio::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define BR_CORE_INFO(...)   ::Brio::Log::GetCoreLogger()->info(__VA_ARGS__)
#define BR_CORE_TRACE(...)  ::Brio::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define BR_CORE_FATAL(...)  ::Brio::Log::GetCoreLogger()->fatal(__VA_ARGS__)

// Client log macros
#define BR_ERROR(...)		::Brio::Log::GetClientLogger()->error(__VA_ARGS__)
#define BR_WARN(...)		::Brio::Log::GetClientLogger()->warn(__VA_ARGS__)
#define BR_INFO(...)		::Brio::Log::GetClientLogger()->info(__VA_ARGS__)
#define BR_TRACE(...)		::Brio::Log::GetClientLogger()->trace(__VA_ARGS__)
#define BR_FATAL(...)		::Brio::Log::GetClientLogger()->fatal(__VA_ARGS__)