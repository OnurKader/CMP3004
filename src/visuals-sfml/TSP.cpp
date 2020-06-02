#include "./Program.hpp"
#include "./Utilities.hpp"
#include "AlgorithmsForVisuals/Genetic.hpp"

#include <SFML/Graphics.hpp>
#include <array>
#include <cmath>
#include <fmt/format.hpp>

#if 0
#define FILE "test.txt"
#else
#define FILE "cities.txt"
#endif

sf::Color getColor(size_t current, size_t max)
{
	return sf::Color(255.f, std::lerp(255.f, 0.f, (current + 0.f) / max), 248.f);
}

void fillVertexArrayWithRegularArray(sf::VertexArray& va, const std::array<uint16_t, 48>& arr)
{
	for(size_t i = 0ULL; i < va.getVertexCount(); ++i)
	{
		va[i].position.x = cities[arr[i]].x;
		va[i].position.y = cities[arr[i]].y;
	}
}

int main()
{
	Program program("../../data/" FILE, 1440U, 920U);
	// [ 0, 5, 1, 6, 3, 7, 2, 4, 0 ]
	// [ 0, 8, 37, 30, 43, 17, 6, 27, 35, 29, 5, 36, 18, 26, 42, 16, 45, 32, 14, 11, 10, 22, 13, 24,
	// 12, 20, 46, 19, 39, 2, 21, 15, 40, 33, 28, 4, 47, 38, 31, 23, 9, 41, 25, 3, 34, 44, 1, 7 ]
	std::array<uint16_t, 48> index_array {0,  8,  37, 30, 43, 17, 6,  27, 35, 29, 5,  36,
										  18, 26, 42, 16, 45, 32, 14, 11, 10, 22, 13, 24,
										  12, 20, 46, 19, 39, 2,  21, 15, 40, 33, 28, 4,
										  47, 38, 31, 23, 9,  41, 25, 3,  34, 44, 1,  7};

	Genetic<uint16_t, cities.size(), 1024ULL> ga(0.015f);
	while(program.window().isOpen())
	{
		// Change vertexArray here to affect the results;
		const float shortest_distance = ga.exec(index_array);

		size_t count = 0ULL;
		for(const size_t i: index_array)
		{
			program.vertexArray()[count].position.x = program.cities()[i].windowPosition().x;
			program.vertexArray()[count].position.y =
				program.window().getSize().y - program.cities()[i].windowPosition().y;
			program.vertexArray()[count].color = getColor(count, index_array.size());
			++count;
		}
		auto& last = program.vertexArray()[program.vertexArray().getVertexCount() - 1ULL];
		last.position.x = program.cities()[0].windowPosition().x;
		last.position.y = program.window().getSize().y - program.cities()[0].windowPosition().y;
		last.color = getColor(48, 48);

		if(!program.run())
			break;
	}

	fmt::print("Thanks! Hope you enjoyed our program ^_^\n");

	return 0;
}
