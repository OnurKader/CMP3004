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
	RepetitiveNearestNeighbour(const size_t repetition_count) :
		m_distance(FLT_MAX),
		m_shortest_distance_yet(FLT_MAX),
		m_repetition_count(repetition_count),
		m_current_repetition_count(0ULL)
	{
		resetArrayToCurrentRepetition();
	};

	std::pair<float, std::array<T, S>> exec(std::array<City, S>& city_arr)
	{
		for(size_t i = 0ULL; i < m_repetition_count; ++i)
		{
			nearestNeighbour(city_arr);
			m_distance = getTotalDistanceOfCities(city_arr, m_array);

			if(m_distance < m_shortest_distance_yet)
			{
				m_shortest_distance_yet = m_distance;
				m_shortest_path_yet = m_array;
			}

			resetVisitedStateForAllCities(city_arr);
		}

		return std::make_pair(m_shortest_distance_yet, m_shortest_path_yet);
	}

private:
	std::array<T, S> m_array;
	std::array<T, S> m_shortest_path_yet;
	float m_distance;
	float m_shortest_distance_yet;
	const size_t m_repetition_count;
	size_t m_current_repetition_count;

	void resetArrayToCurrentRepetition()
	{
		if(m_current_repetition_count >= m_repetition_count)
			return;

		std::generate(m_array.begin(), m_array.end(), [&]() mutable {
			return (m_current_repetition_count++ % S);
		});
	}

	T findNearestCity(std::array<City, S>& city_array, const T queried_index) const
	{
		T closest_index = queried_index;
		float record_distance = FLT_MAX;

		for(size_t i = 0ULL; i < city_array.size(); ++i)
		{
			auto& current_city = city_array[i];
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
		T index_to_query = 0U;
		size_t array_index_to_store_closest_city = 1ULL;
		while(!allCitiesVisited(city_array))
		{
			index_to_query = findNearestCity(city_array, index_to_query);
			m_array[array_index_to_store_closest_city++] = index_to_query;
		}
	}
};
