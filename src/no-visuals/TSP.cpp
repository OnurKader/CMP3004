#include "ExhaustiveSearch.hpp"
#include "NearestNeighbour.hpp"

#include <fmt/format.hpp>

int main()
{
	auto& city_array = cities;
	rt::Timer t_main("Main");

	{
		rt::Timer t_nearest("Nearest Neighbour");
		NearestNeighbour<uint16_t, city_array.size()> nn;
		float distance = nn.exec(city_array, 1U);
		//		ExhaustiveSearch<uint16_t, city_array.size()> es;
		//		float distance = es.exec(city_array, 2U);
		fmt::print("Distance: {}\n", distance);
	}

	return 0;
}
