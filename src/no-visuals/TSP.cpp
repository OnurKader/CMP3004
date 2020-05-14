#include "City.hpp"
#include "ExhaustiveSearch.hpp"
#include "RuntimeUtils.hpp"

int main()
{
	rt::Timer timer("Distance");
	for(size_t i = 0ULL; i < test_cities.size() - 1ULL; ++i)
	{
		std::cout << test_cities[i].dist(test_cities[i + 1ULL]) << '\n';
	}
	std::cout << test_cities.back().dist(test_cities.front()) << '\n';

	return 0;
}
