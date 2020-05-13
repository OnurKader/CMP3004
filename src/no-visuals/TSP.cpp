#include "City.hpp"

#include <chrono>
#include <iostream>
#include <string_view>

using hr_clock = std::chrono::high_resolution_clock;

struct Timer
{
	Timer(std::string_view name) : m_time(hr_clock::now()), m_name(name) {}
	~Timer()
	{
		const auto duration_as_T =
			std::chrono::duration_cast<std::chrono::microseconds>(hr_clock::now() - m_time).count();
		std::cout << m_name << " took " << duration_as_T << " µs\n";
	}

	Timer(const Timer&) = delete;
	Timer(Timer&&) = delete;

	hr_clock::time_point m_time;
	std::string_view m_name;
};

template<typename T, size_t S>
constexpr void printArray(const std::array<T, S>& arr) noexcept
{
	std::cout << "[ ";
	for(size_t i = 0ULL; i < S - 1ULL; ++i)
		std::cout << arr[i] << ", ";
	std::cout << arr.back() << " ]\n";
}

int main()
{
	{
		Timer timer0("Overall Generate + print");
		// 6 elements blow out compiler constexpr range, so I'll leave this now, move on to a
		// different branch and do the runtime version of this
		constexpr auto permutation_arrays = ctx::generateArrays<uint16_t, 5ULL>();

		{
			Timer timer1("Printage");
			for(const auto& arr: permutation_arrays)
				printArray(arr);
		}
	}

	for(size_t i = 0ULL; i < test_cities.size() - 1ULL; ++i)
	{
		std::cout << test_cities[i].dist(test_cities[i + 1ULL]) << '\n';
	}
	std::cout << test_cities.back().dist(test_cities.front()) << '\n';

	return 0;
}
