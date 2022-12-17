#pragma once

#ifdef _KR_DEBUG
#define KR_ENABLE_ASSERTS
#endif

#ifdef KR_ENABLE_ASSERTS
	#define KR_ASSERT_NO_MESSAGE(condition) { if(!(condition)) { KR_ERROR("ASSERTION FAILURE"); __debugbreak(); } }
	#define KR_ASSERT_MESSAGE(condition, ...) { if(!(condition)) { KR_ERROR("ASSERTION FAILURE: {0}", __VA_ARGS__); __debugbreak(); } }

	#define KR_ASSERT_RESOLVE(arg1, arg2, macro, ...) macro
	#define KR_GET_ASSERT_MACRO(...) KR_EXPAND_VARGS(KR_ASSERT_RESOLVE(__VA_ARGS__, KR_ASSERT_MESSAGE, KR_ASSERT_NO_MESSAGE))

	#define KR_ASSERT(...) KR_EXPAND_VARGS( KR_GET_ASSERT_MACRO(__VA_ARGS__)(__VA_ARGS__) )
	#define KR_CORE_ASSERT(...) KR_EXPAND_VARGS( KR_GET_ASSERT_MACRO(__VA_ARGS__)(__VA_ARGS__) )
#else
	#define KR_ASSERT(...)
	#define KR_CORE_ASSERT(...)
#endif