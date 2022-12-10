#include "Kremonte/krpch.h"
#include "Kremonte/src/Core/Log.h"

#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/sinks/basic_file_sink.h"

#include <filesystem>

namespace Kremonte {

	std::shared_ptr<spdlog::logger> Log::s_CoreLogger;
	std::shared_ptr<spdlog::logger> Log::s_ClientLogger;

	void Log::Init() {

		// Create log directory
		std::string logDirectory = "logs";
		if (!std::filesystem::exists(logDirectory)) {
			std::filesystem::create_directories(logDirectory);
		}

		std::vector<spdlog::sink_ptr> aeSinks =
		{
			std::make_shared<spdlog::sinks::stdout_color_sink_mt>(),
			std::make_shared<spdlog::sinks::basic_file_sink_mt>("logs/KREMONTE.log", true)
		};

		std::vector<spdlog::sink_ptr> appSinks =
		{
			std::make_shared<spdlog::sinks::stdout_color_sink_mt>(),
			std::make_shared<spdlog::sinks::basic_file_sink_mt>("logs/APPLICATION.log", true)
		};

		aeSinks[0]->set_pattern("%^[%T] %n: %v%$");
		aeSinks[1]->set_pattern("[%T] [%1] %n: %v");
		appSinks[0]->set_pattern("%^[%T] %n: %v%$");
		appSinks[1]->set_pattern("[%T] [%1] %n: %v");


		s_CoreLogger = std::make_shared<spdlog::logger>("KREMONTE", aeSinks.begin(), aeSinks.end());
		s_CoreLogger->set_level(spdlog::level::trace);
		
		s_ClientLogger = std::make_shared<spdlog::logger>("APPLICATION", appSinks.begin(), appSinks.end());
		s_ClientLogger->set_level(spdlog::level::trace);
	}

	void Log::Shutdown() {
		s_ClientLogger.reset();
		s_CoreLogger.reset();
		spdlog::drop_all();
	}

}
