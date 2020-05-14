#pragma once

#include "ConstexprUtils.hpp"

#include <vector>

struct City final
{
	constexpr City(const uint16_t _x, const uint16_t _y) : x(_x), y(_y), visited(false) {}
	constexpr float dist(const City& other) const noexcept
	{
		const uint16_t _x = std::max(x, other.x) - std::min(x, other.x);
		const uint16_t _y = std::max(y, other.y) - std::min(y, other.y);
		return ctx::sqrt((_x * _x) + (_y * _y));
	}

	constexpr void toggleVisited() noexcept { visited = !visited; }

	uint16_t x;
	uint16_t y;
	bool visited;
};

[[maybe_unused]] constexpr static std::array cities {
	City(6734, 1453), City(2233, 10),	City(5530, 1424), City(401, 841),	City(3082, 1644),
	City(7608, 4458), City(7573, 3716), City(7265, 1268), City(6898, 1885), City(1112, 2049),
	City(5468, 2606), City(5989, 2873), City(4706, 2674), City(4612, 2035), City(6347, 2683),
	City(6107, 669),  City(7611, 5184), City(7462, 3590), City(7732, 4723), City(5900, 3561),
	City(4483, 3369), City(6101, 1110), City(5199, 2182), City(1633, 2809), City(4307, 2322),
	City(675, 1006),  City(7555, 4819), City(7541, 3981), City(3177, 756),	City(7352, 4506),
	City(7545, 2801), City(3245, 3305), City(6426, 3173), City(4608, 1198), City(23, 2216),
	City(7248, 3779), City(7762, 4595), City(7392, 2244), City(3484, 2829), City(6271, 2135),
	City(4985, 140),  City(1916, 1569), City(7280, 4899), City(7509, 3239), City(10, 2676),
	City(6807, 2993), City(5185, 3258), City(3023, 1942)};

[[maybe_unused]] constexpr static std::array test_cities {City(56, 220),
														  City(700, 1003),
														  City(3520, 17),
														  City(455, 3206),
														  City(5879, 6238),
														  City(121, 617),
														  City(99, 2000),
														  City(4621, 3023)};

// Find the total distance of a given array of Cities
template<size_t S>
constexpr float getTotalDistanceOfCities(const std::array<City, S>& city_arr,
										 const std::array<uint16_t, S>& index_array) noexcept
{
	float result = 0ULL;

	for(size_t i = 0ULL; i < index_array.size() - 1ULL; ++i)
	{
		auto index = index_array[i];
		result += city_arr[index].dist(city_arr[index + 1ULL]);
	}

	result += city_arr[index_array.front()].dist(city_arr[index_array.back()]);

	return result;
}
