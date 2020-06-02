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
	rt::Timer main_timer("Main");

	{
		rt::Timer algorithm_timer("Genetic Algorithm");

		constexpr size_t population_size = 2048ULL;
		constexpr float mutation_rate = 0.01f;
		Genetic<uint16_t, city_array.size(), population_size> gen(mutation_rate);
		const auto& [distance, shortest_path] = gen.exec(1U);
		fmt::print("Final Distance: {}\nFinal Array: {}\n", distance, shortest_path);
	}

	return 0;
}
