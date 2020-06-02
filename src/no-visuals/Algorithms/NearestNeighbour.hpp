#pragma once

#include "City.hpp"
#include "Utilities.hpp"

#include <algorithm>
#include <array>
#include <cfloat>
#include <fmt/format.hpp>
#include <fmt/ostream.hpp>
#include <fstream>
#include <numeric>

template<typename T, size_t S>
class NearestNeighbour final
{
public:
	NearestNeighbour() : m_index_array{0U} {}

	std::pair<float, std::array<T, S>> exec(std::array<City, S>& city_array,
											const uint8_t log_level = 0U)
	{
		T nearest_city_index = 0U;
		size_t index_to_store_nearest_city = 0ULL;
		// Do this while all the cities are unvisited
		while(!allCitiesVisited(city_array))
		{
			nearest_city_index = getNearestCityIndex(city_array, nearest_city_index);
			if(nearest_city_index == 0U)
				break;	  // Means all the cities are visited, shouldn't break anything but hey
			m_index_array[++index_to_store_nearest_city] = nearest_city_index;

			switch(log_level)
			{
				case 0U: break;
				case 1U:
					fmt::print("{}: ({}, {})\n",
							   nearest_city_index,
							   city_array[nearest_city_index].x,
							   city_array[nearest_city_index].y);
					break;
				default: break;
			}
		}

		if(log_level)
			fmt::print("m_index_array: {}\n", m_index_array);

		const float distance_of_nn_path = getTotalDistanceOfCities(city_array, m_index_array);

		std::ofstream out_file{"nn_output.txt"};
		if(out_file)
		{
			fmt::print(out_file, "{}\nDistance: {}\n", m_index_array, distance_of_nn_path);
			out_file.flush();
		}

		return std::make_pair(distance_of_nn_path, m_index_array);
	}

private:
	std::array<T, S> m_index_array;

	T getNearestCityIndex(std::array<City, S>& city_array, const T index_to_query)
	{
		float min_distance = FLT_MAX;
		T nearest_city_index = 0U;

		for(size_t i = 0ULL; i < city_array.size(); ++i)
		{
			auto& current_city = city_array[i];
			if(!current_city.visited && i != index_to_query)
			{
				const float dist_between_current_and_queried_city =
					current_city.dist(city_array[index_to_query]);

				if(dist_between_current_and_queried_city < min_distance)
				{
					min_distance = dist_between_current_and_queried_city;
					nearest_city_index = static_cast<T>(i);
				}
			}
		}

		city_array[nearest_city_index].visited = true;
		city_array[index_to_query].visited = true;

		return nearest_city_index;
	}
};
