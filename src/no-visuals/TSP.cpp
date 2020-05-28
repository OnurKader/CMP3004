#include "ExhaustiveSearch.hpp"
#include "NearestNeighbour.hpp"
#include "RepetitiveNearestNeighbour.hpp"

#include <fmt/format.hpp>

int main()
{
	auto& city_array = cities;
	rt::Timer t_main("Main");

	{
		rt::Timer t_algo("Repetitive Nearest Neighbour");
		//		NearestNeighbour<uint16_t, city_array.size()> nn;
		//		const auto& [distance, shortest_path] = nn.exec(city_array, 1U);
		//		ExhaustiveSearch<uint16_t, city_array.size()> es;
		//		float distance = es.exec(city_array, 2U);
		RepetitiveNearestNeighbour<uint16_t, city_array.size()> rnn(city_array.size());
		const auto& [distance, shortest_path] = rnn.exec(city_array);
		fmt::print("Distance: {}\nArray: {}\n", distance, shortest_path);
	}

	return 0;
}
