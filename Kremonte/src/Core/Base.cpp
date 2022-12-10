#include "Kremonte/krpch.h"

#include "Kremonte/src/Core/Base.h"
#include "Kremonte/src/Core/Log.h"

#define KR_BUILD_ID "v0.1a"

namespace Kremonte {

	void InitializeCore() {
		Log::Init();

		KR_CORE_TRACE("KREMONTE {}", KR_BUILD_ID);
		KR_CORE_TRACE("Beginning initialization...");
	}

	void ShutdownCore() {
		KR_CORE_TRACE("Shutting down...");

		Log::Shutdown();
	}
}