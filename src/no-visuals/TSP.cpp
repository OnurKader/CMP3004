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
		const float distance = nn.exec(city_array, 0U);
		std::cout << "Distance: " << distance << '\n';
	}

	return 0;
}
