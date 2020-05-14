#include "City.hpp"
#include "ExhaustiveSearch.hpp"

#include <iostream>

int main()
{
	constexpr auto& city_array = cities;
	rt::Timer main("Main");

	{
		rt::Timer exhaustive("Exhaustive Search");
		ExhaustiveSearch<uint16_t, city_array.size()> es;
		es.exec(city_array, 2U);
	}

	return 0;
}
