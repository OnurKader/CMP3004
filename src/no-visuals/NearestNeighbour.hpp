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
	NearestNeighbour() : m_shortest_distance(FLT_MAX), m_prev_shortest_distance(m_shortest_distance)
	{
		std::iota(m_array.begin(), m_array.end(), T {});
		m_shortest_path.fill(T {});
	}

	struct NearestCity
	{
		City& city;
		uint16_t index;
		float distance;
	};

	float exec(std::array<City, S>& city_array, const uint8_t log_level = 0U)
	{
		for(auto&& city: city_array)
		{
			const auto nc = findNearestCity(city_array, city);
			switch(log_level)
			{
				case 0U: break;
				case 1U:
					//					std::cout << nc.distance << " units and City index " << nc.index
					//<< std::endl;
					break;
			}
			rt::setVisitedOfCities(city_array, false);
		}

		return m_shortest_distance;
	}

	private:
	std::array<T, S> m_array;
	std::array<T, S> m_shortest_path;
	float m_shortest_distance;
	float m_prev_shortest_distance;

	// Utility function that traverses through all the cities and finds the smallest distance from
	// the current one and marks it as visited at the end, maybe mark out city as visited as well
	constexpr NearestCity findNearestCity(std::array<City, S>& city_array, City& city) const
	{
		float shortest_distance_yet = FLT_MAX;
		uint16_t shortest_distance_index = UINT16_MAX;
		NearestCity nc(city, 0U, FLT_MAX);

		for(size_t i = 0ULL; i < city_array.size(); ++i)
		{
			auto& current_city = city_array[i];
			if(!current_city.visited && city != current_city)
			{
				// Do the actual work ?
				const float dist = city.dist(current_city);
				if(dist < shortest_distance_yet)
				{
					std::cout << "Dist: " << dist << " shortest_yet: " << shortest_distance_yet
							  << std::endl;
					shortest_distance_yet = dist;
					shortest_distance_index = i;
					current_city.visited = true;
					city.visited = true;

					nc.city = current_city;
					nc.index = i;
					nc.distance = dist;
				}
			}
		}

		return nc;
	}
};
