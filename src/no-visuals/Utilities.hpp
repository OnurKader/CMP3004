#pragma once

#include <algorithm>
#include <array>
#include <chrono>
#include <cmath>
#include <fmt/format.hpp>
#include <numeric>
#include <string_view>

namespace ctx
{
namespace integ
{
template<typename T>
constexpr T sqrt_helper(const T x, const T lo, const T hi) noexcept
{
	if(lo == hi)
		return lo;

	const T mid = (lo + hi + 1) / 2;

	if(x / mid < mid)
		return sqrt_helper<T>(x, lo, mid - 1);
	else
		return sqrt_helper(x, mid, hi);
}

template<typename T>
constexpr T sqrt(const T x) noexcept
{
	return sqrt_helper<T>(x, 0, x / 2 + 1);
}
}	 // namespace integ

constexpr float sqrtNewtonRaphson(const float x, const float curr, const float prev)
{
	return curr == prev ? curr : sqrtNewtonRaphson(x, 0.5f * (curr + x / curr), curr);
}

constexpr float sqrt(const float x) noexcept
{
	return x >= 0.f && x < std::numeric_limits<float>::infinity()
			   ? sqrtNewtonRaphson(x, x, 0.f)
			   : std::numeric_limits<float>::quiet_NaN();
}

template<typename T, size_t S>
constexpr std::array<T, S> makeAndFillArray() noexcept
{
	std::array<T, S> temp;
	std::iota(temp.begin(), temp.end(), 0ULL);
	return temp;
}

constexpr size_t factorial(size_t num) noexcept
{
	size_t result = num;
	while(--num)
		result *= num;
	return result;
}

template<typename T, size_t S>
constexpr void permutate(std::array<T, S>& arr, const size_t n)
{
	for(size_t i = 0ULL; i < n; ++i)
		std::next_permutation(arr.begin(), arr.end());
}

template<typename T, size_t S>
constexpr std::array<std::array<T, S>, factorial(S)> generateArrays()
{
	std::array<std::array<T, S>, factorial(S)> temp;
	std::generate(temp.begin(), temp.end(), makeAndFillArray<T, S>);
	size_t index = 0ULL;
	std::for_each(
		temp.begin(), temp.end(), [&index](auto&& arr) constexpr { permutate(arr, index++); });
	return temp;
}

}	 // namespace ctx

namespace rt
{
using hr_clock = std::chrono::high_resolution_clock;

struct Timer final
{
	Timer(const std::string_view name) : m_time(hr_clock::now()), m_name(name) {}
	~Timer()
	{
		const int64_t duration_as_T =
			std::chrono::duration_cast<std::chrono::microseconds>(hr_clock::now() - m_time).count();
		fmt::print("{} took {} µs, {} ms\n", m_name, duration_as_T, duration_as_T / 1000L);
	}

	Timer(const Timer&) = delete;
	Timer(Timer&&) = delete;

	auto operator=(const Timer&) = delete;
	auto operator=(Timer&&) = delete;

	const hr_clock::time_point m_time;
	const std::string_view m_name;
};

}	 // namespace rt

// {fmt} custom formatters
template<typename T, size_t S>
struct fmt::formatter<std::array<T, S>>
{
	constexpr auto parse(format_parse_context& ctx) { return ctx.begin(); }

	template<typename FormatContext>
	auto format(const std::array<T, S>& arr, FormatContext& ctx)
	{
		format_to(ctx.out(), "[");
		for(size_t i = 0ULL; i < arr.size() - 1ULL; ++i)
			format_to(ctx.out(), "{}, ", arr[i]);
		return format_to(ctx.out(), "{}]", arr.back());
	}
};

template<typename T>
struct fmt::formatter<std::vector<T>>
{
	constexpr auto parse(format_parse_context& ctx) { return ctx.begin(); }

	template<typename FormatContext>
	auto format(const std::vector<T>& vec, FormatContext& ctx)
	{
		format_to(ctx.out(), "[");
		for(size_t i = 0ULL; i < vec.size() - 1ULL; ++i)
			format_to(ctx.out(), "{}, ", vec[i]);
		return format_to(ctx.out(), "{}]", vec.back());
	}
};

template<typename T1, typename T2>
struct fmt::formatter<std::pair<T1, T2>>
{
	constexpr auto parse(format_parse_context& ctx) { return ctx.begin(); }

	template<typename FormatContext>
	auto format(const std::pair<T1, T2>& pair, FormatContext& ctx)
	{
		return format_to(ctx.out(), "({}, {})", pair.first, pair.second);
	}
};
