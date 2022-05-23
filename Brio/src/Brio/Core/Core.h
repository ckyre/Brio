#pragma once
#include <memory>

#ifdef BR_ENABLE_ASSERTS
	#define BR_ASSERT(x, ...) { if(!(x)) { BR_ERROR("Assertion failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define BR_CORE_ASSERT(x, ...) { if(!(x)) { BR_CORE_ERROR("Assertion failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define BR_ASSERT(x, ...)
	#define BR_CORE_ASSERT(x, ...)
#endif


#define BIT(x) (1 << x)

#define BR_BIND_EVENT_FUNC(func) std::bind(&func, this, std::placeholders::_1

namespace Brio
{
	template<typename T>
	using Scope = std::unique_ptr<T>;

	template<typename T>
	using Ref = std::shared_ptr<T>;
}