#pragma once

#include "Kremonte/src/Core/Assert.h"
#include <memory>

namespace Kremonte {

	void InitializeCore();
	void ShutdownCore();

}

#ifndef _KR_PLATFORM_WINDOWS_
	#error KREMONTE only supports Windows!
#endif

#define KR_EXPAND_VARGS(x) x
#define BIT(x) (1 << x)
#define KR_BIND_EVENT_FN(fn) std::bind(&##fn, this, std::placeholders::_1)

//#include "Assert.h"

namespace Kremonte {

	template<typename T>
	using Scope = std::unique_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Scope<T> CreateScope(Args&& ... args) {
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	using byte = uint8_t;

}