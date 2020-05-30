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

		RepetitiveNearestNeighbour<uint16_t, city_array.size()> nn;
		const auto& [distance, shortest_path] = nn.exec(city_array, 47ULL, 0U);
		fmt::print("Distance: {}\nArray: {}\n", distance, shortest_path);
	}

	return 0;
}
