#pragma once

#include "City.hpp"
#include "ConstexprUtils.hpp"
#include "RuntimeUtils.hpp"

#include <array>
#include <cfloat>
#include <numeric>

// Inheritance with a base class of Algorithm which holds the arrays and the distance, also the exec
// function
template<typename T, size_t S>
class NearestNeighbour final
{
	public:
	NearestNeighbour()
	{
		std::iota(m_index_array.begin(), m_index_array.end(), T {});
		//		m_index_array.back() = 0U;
	}

	float exec(std::array<City, S>& city_array, const uint8_t log_level = 0U)
	{
		uint16_t index_to_query = 0U;
		size_t array_index_to_store_closest_city = 1ULL;
		while(!std::all_of(
			city_array.cbegin(), city_array.cend(), [](const auto& elem) { return elem.visited; }))
		{
			index_to_query = findNearestCity(city_array, index_to_query);

			// Store the next city's index in the array
			m_index_array[array_index_to_store_closest_city++] = index_to_query;

			// Recursion with the returned city?

			switch(log_level)
			{
				case 0U: break;
				default:
					std::cout << index_to_query << ": (" << city_array[index_to_query].x << ", "
							  << city_array[index_to_query].y << ")\n";
			}
		}

		// Everything is visited, connect last visited city with the first one
		//		rt::printArray(m_index_array);

		return getTotalDistanceOfCities(city_array, m_index_array);
	}

	private:
	std::array<T, S> m_index_array;

	// Utility function that traverses through all the cities and finds the smallest distance from
	// the current one and marks it as visited at the end, maybe mark our city as visited as well

	// Should this just return the index, or maybe the index + distance in an std::pair
	// No real reason to get the city, we just hold the indices for the edges
	uint16_t findNearestCity(std::array<City, S>& city_array, const uint16_t queried_index) const
	{
		uint16_t closest_index = queried_index;
		float record_distance = FLT_MAX;

		for(size_t i = 0ULL; i < city_array.size(); ++i)
		{
			auto& current_city = city_array[i];
			if(!current_city.visited && queried_index != i)
			{
				const float distance = rt::dist(city_array[queried_index], current_city);
//				std::cout << "Distance (" << city_array[queried_index].x << ", "
//						  << city_array[queried_index].y << ") and (" << current_city.x << ", "
//						  << current_city.y << ") is " << distance << std::endl;
				if(distance < record_distance)
				{
					closest_index = i;
					record_distance = distance;
				}
			}
		}

		// Set the city we gave and the closest one to it as visited, I'm not checking to see if the
		// city passed to this function is visited or not so it's safe to mark the closest as
		// visited, it can find a non-visited city for itself, and if it can't find one, that means
		// that the whole array has been visited and it's time to connect the last city with the
		// first one to complete our cycle.
		city_array[queried_index].visited = true;
		city_array[closest_index].visited = true;

		return closest_index;
	}
};
