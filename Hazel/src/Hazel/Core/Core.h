#pragma once

#ifdef HZ_PLATFORM_WINDOWS
#if HZ_DYNAMIC_LINK
	#ifdef HZ_BUILD_DLL
		#define HAZEL_API __declspec(dllexport)
	#else
		#define HAZEL_API __declspec(dllimport)
	#endif
#else
	#define HAZEL_API
#endif
#else
	#error Hazel only support Windows!
#endif

#ifdef HZ_ENABLE_ASSERTS
	#define HZ_ASSERTS(x, ...) { if (!(x)) { HZ_ERROR("Assertion Failed : {0}", __VAR_ARGS__); __debugbreak(); } }
	#deinfe HZ_CORE_ASSERT(x, ...) { if (!(x)) { HZ_CORE_ERROR("Assertion Failed : {0}", __VAR_ARGS__); __debugbreak(); } }
#else
	#define HZ_ASSERT(x, ...)
	#define HZ_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)