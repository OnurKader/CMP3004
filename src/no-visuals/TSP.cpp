#include "ExhaustiveSearch.hpp"
#include "Genetic.hpp"
#include "NearestNeighbour.hpp"
#include "Random.hpp"
#include "RepetitiveNearestNeighbour.hpp"
#include "Utilities.hpp"

#include <fmt/format.hpp>

int main()
{
	// For the Genetic Algorithm the city array also needs to be changed in DNA.hpp, sorry for the
	// inconvenience
	auto& city_array = cities;
	rt::Timer t_main("Main");

	{
		rt::Timer t_algo("Genetic Algorithm");

		constexpr size_t population_size = 512ULL;

		Genetic<uint16_t, city_array.size(), population_size> gen;
		const auto& [distance, shortest_path] = gen.exec(1U);
		fmt::print("Final Distance: {}\nArray: {}\n", distance, shortest_path);
	}

	return 0;
}
