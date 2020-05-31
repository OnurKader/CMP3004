#include "ExhaustiveSearch.hpp"
#include "Genetic.hpp"
#include "NearestNeighbour.hpp"
#include "RepetitiveNearestNeighbour.hpp"
#include "Utilities.hpp"

#include <fmt/format.hpp>

int main()
{
	auto& city_array = cities;
	rt::Timer t_main("Main");

	{
		rt::Timer t_algo("Genetic Algorithm");

		Genetic<uint16_t, city_array.size()> gen;
		const auto& [distance, shortest_path] = gen.exec(city_array, 1U);
		fmt::print("Distance: {}\nArray: {}\n", distance, shortest_path);
	}

	return 0;
}
