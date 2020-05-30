#pragma once

#include "City.hpp"
#include "Utilities.hpp"

#include <algorithm>
#include <array>
#include <cfloat>
#include <fmt/format.hpp>
#include <fstream>
#include <numeric>

template<typename T, size_t S>
class RepetitiveNearestNeighbour
{
public:
	RepetitiveNearestNeighbour() :
		m_current_path_array {0U},
		m_shortest_path_yet {0U},
		m_distance(FLT_MAX),
		m_shortest_distance_yet(FLT_MAX),
		m_current_repetition_count(0ULL) {};

	std::pair<float, std::array<T, S>> exec(std::array<City, S>& city_arr,
											const size_t repetition_count = 47ULL,
											const uint8_t log_level = 0U)
	{
		for(size_t i = 0ULL; i < repetition_count; ++i)
		{
			nearestNeighbour(city_arr);
			m_distance = getTotalDistanceOfCities(city_arr, m_current_path_array);

			if(m_distance < m_shortest_distance_yet)
			{
				m_shortest_distance_yet = m_distance;
				m_shortest_path_yet = m_current_path_array;
			}

			if(log_level)
			{
				fmt::print("exec::for i={}, arr={}\n", i, m_current_path_array);
				fmt::print("exec::for i={}, spy={}\n\n", i, m_shortest_path_yet);
			}

			resetVisitedStateForAllCities(city_arr);
			m_current_repetition_count = (m_current_repetition_count + 1ULL) % S;
			m_current_path_array.front() = m_current_repetition_count;
		}

		return std::make_pair(m_shortest_distance_yet, m_shortest_path_yet);
	}

private:
	std::array<T, S> m_current_path_array;
	std::array<T, S> m_shortest_path_yet;
	float m_distance;
	float m_shortest_distance_yet;
	size_t m_current_repetition_count;

	T findNearestCity(std::array<City, S>& city_array, const T queried_index) const
	{
		T closest_index = queried_index;
		float record_distance = FLT_MAX;

		size_t counter = 0ULL;
		for(size_t i = m_current_repetition_count; counter < S; i = (i + 1ULL) % S, ++counter)
		{
			const auto& current_city = city_array[i];
			if(!current_city.visited && queried_index != i)
			{
				const float distance = city_array[queried_index].dist(current_city);
				if(distance < record_distance)
				{
					closest_index = static_cast<T>(i);
					record_distance = distance;
				}
			}
		}

		city_array[queried_index].visited = true;
		city_array[closest_index].visited = true;

		return closest_index;
	}

	void nearestNeighbour(std::array<City, S>& city_array)
	{
		T index_to_query = m_current_repetition_count;
		size_t array_index_to_store_closest_city = 0ULL;
		while(!allCitiesVisited(city_array))
		{
			index_to_query = findNearestCity(city_array, index_to_query);
			if(index_to_query == 0U)
				break;
			m_current_path_array[++array_index_to_store_closest_city] = index_to_query;
		}
	}
};
