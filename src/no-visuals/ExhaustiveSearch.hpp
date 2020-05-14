#pragma once

#include "City.hpp"
#include "ConstexprUtils.hpp"
#include "RuntimeUtils.hpp"

#include <cfloat>
#include <iomanip>

template<typename T, size_t S>
class ExhaustiveSearch
{
	public:
	constexpr ExhaustiveSearch() :
		m_shortest_distance(FLT_MAX), m_prev_shortest_distance(m_shortest_distance)
	{
		std::iota(m_array.begin(), m_array.end(), T {});
		// Default initialize the array or assign to m_array's current, beginning, state?
		m_shortest_path.fill(T {});
	}

	// TODO: Store the shortest path in the array and save it to a local file at the end of
	// Exhaustive Search's life?

	// Multi-threaded for_each?
	float exec(const std::array<City, S>& city_array, const uint8_t log_level = 0U)
	{
		for(size_t i = 0ULL; i < ctx::factorial(m_array.size()); ++i)
		{
			m_shortest_distance =
				std::min(getTotalDistanceOfCities(city_array, m_array), m_shortest_distance);

			switch(log_level)
			{
				case 0: break;
				case 1: rt::printArray(m_array); [[fallthrough]];
				default:
					if(m_shortest_distance < m_prev_shortest_distance)
						std::cout << std::fixed << std::setprecision(3) << m_shortest_distance
								  << std::endl;
			}

			ctx::permutate(m_array, 1ULL);
			m_prev_shortest_distance = m_shortest_distance;
		}

		return m_shortest_distance;
	}

	private:
	// Just keeping the shortest distance is enough right?
	std::array<T, S> m_array;
	std::array<T, S> m_shortest_path;
	float m_shortest_distance;
	float m_prev_shortest_distance;
};
