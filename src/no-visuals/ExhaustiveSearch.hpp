#pragma once

#include "City.hpp"
#include "Utilities.hpp"

#include <cfloat>
#include <fmt/format.hpp>
#include <fmt/ostream.hpp>
#include <fstream>

template<typename T, size_t S>
class ExhaustiveSearch
{
public:
	constexpr ExhaustiveSearch() :
		m_shortest_distance(FLT_MAX), m_prev_shortest_distance(m_shortest_distance)
	{
		std::iota(m_array.begin(), m_array.end(), T {});
		// Default initialize the array or assign to m_array's current, beginning, state?

		// FIXME: Just member initialize list?
		m_shortest_path.fill(T {});
	}

	// Multi-threaded for_each?
	float exec(const std::array<City, S>& city_array, const uint8_t log_level = 0U)
	{
		for(size_t i = 0ULL; i < ctx::factorial(m_array.size()); ++i)
		{
			const auto dist = getTotalDistanceOfCities(city_array, m_array);
			if(m_shortest_distance < dist)
			{
				m_shortest_distance = dist;
				m_shortest_path = m_array;
			}

			switch(log_level)
			{
				case 0: break;
				case 1: fmt::print("{}\n", m_array); [[fallthrough]];
				default:
					if(m_shortest_distance < m_prev_shortest_distance)
						fmt::print("{:.3}\n", m_shortest_distance);
			}

			ctx::permutate(m_array, 1ULL);
			m_prev_shortest_distance = m_shortest_distance;
		}

		// TODO: save to file here
		std::ofstream exhaustive_out("exhaustive-out.txt");
		if(exhaustive_out)
			fmt::print(exhaustive_out, "{}\n", m_array);

		return m_shortest_distance;
	}

private:
	// Just keeping the shortest distance is enough right?
	std::array<T, S> m_array;
	std::array<T, S> m_shortest_path;
	float m_shortest_distance;
	float m_prev_shortest_distance;
};
