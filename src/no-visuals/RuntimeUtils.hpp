#pragma once

#include "City.hpp"

#include <array>
#include <chrono>
#include <cmath>
#include <iostream>
#include <string_view>

namespace rt
{
template<typename T, size_t S>
void printArray(const std::array<T, S>& arr) noexcept
{
	std::cout << "[ ";
	for(size_t i = 0ULL; i < S - 1ULL; ++i)
		std::cout << arr[i] << ", ";
	std::cout << arr.back() << " ]\n";
}

using hr_clock = std::chrono::high_resolution_clock;

struct Timer final
{
	Timer(const std::string_view name) : m_time(hr_clock::now()), m_name(name) {}
	~Timer()
	{
		const int64_t duration_as_T =
			std::chrono::duration_cast<std::chrono::microseconds>(hr_clock::now() - m_time).count();
		std::cout << m_name << " took " << duration_as_T << " µs, " << duration_as_T / 1000L
				  << " ms\n";
	}

	Timer(const Timer&) = delete;
	Timer(Timer&&) = delete;

	auto operator=(const Timer&) = delete;
	auto operator=(Timer&&) = delete;

	const hr_clock::time_point m_time;
	const std::string_view m_name;
};

inline float dist(const City& first, const City& second)
{
	const float dx = second.x - first.x;
	const float dy = second.y - first.y;
	return std::hypot(dx, dy);
}

template<size_t S>
float getTotalDistanceOfCities(const std::array<City, S>& city_arr,
							   const std::array<uint16_t, S>& index_array)
{
	float result = 0.f;

	for(size_t i = 0ULL; i < index_array.size() - 1ULL; ++i)
	{
		auto index = index_array[i];
		result += dist(city_arr[index], city_arr[index + 1ULL]);
	}

	result += dist(city_arr[index_array.front()], city_arr[index_array.back()]);

	return result;
}
}	 // namespace rt
