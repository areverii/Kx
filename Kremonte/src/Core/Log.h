#pragma once

#include "Kremonte/src/Core/Base.h"

#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h" // for logging custom types

namespace Kremonte {

	class Log
	{

	public:
		static void Init();
		static void Shutdown();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};

}

/*template<typename ostream>
ostream& operator<<(ostream& os, const glm::vec4& vec) {
	return os << '(' << vec.x << ", " << vec.y << ", " << vec.z <<", " << vec.w << ")";
}*/

// Core log macros
#define KR_CORE_TRACE(...)     ::Kremonte::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define KR_CORE_INFO(...)      ::Kremonte::Log::GetCoreLogger()->info(__VA_ARGS__)
#define KR_CORE_WARN(...)      ::Kremonte::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define KR_CORE_ERROR(...)     ::Kremonte::Log::GetCoreLogger()->error(__VA_ARGS__)
#define KR_CORE_FATAL(...)     ::Kremonte::Log::GetCoreLogger()->fatal(__VA_ARGS__)

// Client log macros
#define KR_TRACE(...)          ::Kremonte::Log::GetClientLogger()->trace(__VA_ARGS__)
#define KR_INFO(...)           ::Kremonte::Log::GetClientLogger()->info(__VA_ARGS__)
#define KR_WARN(...)           ::Kremonte::Log::GetClientLogger()->warn(__VA_ARGS__)
#define KR_ERROR(...)          ::Kremonte::Log::GetClientLogger()->error(__VA_ARGS__)
#define KR_FATAL(...)          ::Kremonte::Log::GetClientLogger()->fatal(__VA_ARGS__)