#pragma once

#include "City.hpp"

#include <algorithm>
#include <array>
#include <cstdint>
#include <numeric>

namespace ctx
{
namespace integ
{
template<typename T>
constexpr T sqrt_helper(T x, T lo, T hi) noexcept
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
constexpr T sqrt(T x) noexcept
{
	return sqrt_helper<T>(x, 0, x / 2 + 1);
}
}	 // namespace integ

constexpr float sqrtNewtonRaphson(float x, float curr, float prev)
{
	return curr == prev ? curr : sqrtNewtonRaphson(x, 0.5 * (curr + x / curr), curr);
}

constexpr float sqrt(float x) noexcept
{
	return x >= 0. && x < std::numeric_limits<float>::infinity()
			   ? sqrtNewtonRaphson(x, x, 0)
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
