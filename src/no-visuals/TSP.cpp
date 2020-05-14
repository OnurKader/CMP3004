#include "City.hpp"
#include "ExhaustiveSearch.hpp"
#include "NearestNeighbour.hpp"

#include <iostream>

int main()
{
	auto& city_array = test_cities;
	rt::Timer t_main("Main");

	{
		rt::Timer t_nearest("Nearest Neighbour");
		NearestNeighbour<uint16_t, city_array.size()> nn;
		nn.exec(city_array, 1U);
	}

	return 0;
}
