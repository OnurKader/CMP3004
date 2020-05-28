#include "ExhaustiveSearch.hpp"
#include "NearestNeighbour.hpp"
#include "RepetitiveNearestNeighbour.hpp"
#include "Utilities.hpp"

#include <fmt/format.hpp>

int main()
{
	auto& city_array = cities;
	rt::Timer t_main("Main");

	{
		rt::Timer t_algo("Repetitive Nearest Neighbour");

		NearestNeighbour<uint16_t, city_array.size()> nn;
		const auto& [distance, shortest_path] = nn.exec(city_array, 0U);
		fmt::print("Distance: {}\nArray: {}\n", distance, shortest_path);
		for(size_t i = 0ULL; i < city_array.size() - 1ULL; ++i)
		{
			const auto& city = city_array[i];
			const auto& next_city = city_array[i + 1ULL];
			fmt::print("Dist betw. {}({},{})-{}({},{}) = {}\n",
					   shortest_path[i],
					   city.x,
					   city.y,
					   shortest_path[i + 1ULL],
					   next_city.x,
					   next_city.y,
					   city_array[shortest_path[i]].dist(city_array[shortest_path[i + 1ULL]]));
		}
	}

	return 0;
}
