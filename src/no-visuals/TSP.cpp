//#include "ExhaustiveSearch.hpp"
#include "NearestNeighbour.hpp"

#include <iostream>

int main()
{
	auto& city_array = cities;
	rt::Timer t_main("Main");

	{
		rt::Timer t_nearest("Nearest Neighbour");
		NearestNeighbour<uint16_t, city_array.size()> nn;
		float distance = nn.exec(city_array, 0U);
		distance += 1.f;
		std::cout << "Distance: " << distance << std::endl;
	}

	return 0;
}
