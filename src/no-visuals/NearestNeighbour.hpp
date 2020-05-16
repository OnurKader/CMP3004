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
	NearestNeighbour() : m_shortest_distance(FLT_MAX)
	{
		std::iota(m_array.begin(), m_array.end(), T {});
		m_shortest_path.fill(T {});
	}

	struct NearestCity
	{
		City city;
		uint16_t index;
		float distance;
	};

	float exec(std::array<City, S>& city_array, const uint8_t log_level = 0U)
	{
		uint16_t index_to_query = 0U;
		while(std::all_of(
			city_array.cbegin(), city_array.cend(), [](const auto& elem) { return elem.visited; }))
		{
			const NearestCity nc = findNearestCity(city_array, index_to_query);
			// Recursion with the returned city?

			switch(log_level)
			{
				case 0U: break;
				default:
					std::cout << nc.distance << " units and City index " << nc.index << std::endl;
			}
		}

		// Everything is visited, connect last visited city with the first one

		return m_shortest_distance;
	}

	private:
	std::array<T, S> m_array;
	std::array<T, S> m_shortest_path;
	float m_shortest_distance;

	// Utility function that traverses through all the cities and finds the smallest distance from
	// the current one and marks it as visited at the end, maybe mark our city as visited as well

	// Should this just return the index, or maybe the index + distance in an std::pair
	// No real reason to get the city, we just hold the indices for the edges
	NearestCity findNearestCity(std::array<City, S>& city_array, const uint16_t queried_index) const
	{
		NearestCity nc {city_array[queried_index], 0ULL, FLT_MAX};

		for(size_t i = 0ULL; i < city_array.size(); ++i)
		{
			auto& current_city = city_array[i];
			if(!current_city.visited && queried_index != i)
			{
				const float dist = city_array[queried_index].dist(current_city);
				if(dist < nc.distance)
				{
					// Store the closest city
					nc.city = current_city;
					nc.index = i;
					nc.distance = dist;
				}
			}
		}

		// Set the city we gave and the closest one to it as visited, I'm not checking to see if the
		// city passed to this function is visited or not so it's safe to mark the closest as
		// visited, it can find a non-visited city for itself, and if it can't find one, that means
		// that the whole array has been visited and it's time to connect the last city with the
		// first one to complete our cycle.
		city_array[queried_index].visited = true;
		nc.city.visited = true;

		return nc;
	}
};
