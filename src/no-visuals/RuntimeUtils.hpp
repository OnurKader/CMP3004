#pragma once

#include "City.hpp"

#include <array>
#include <chrono>
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
		std::clog << m_name << " took " << duration_as_T << " µs, " << duration_as_T / 1000L
				  << " ms\n";
	}

	Timer(const Timer&) = delete;
	Timer(Timer&&) = delete;

	const hr_clock::time_point m_time;
	const std::string_view m_name;
};

}	 // namespace rt
