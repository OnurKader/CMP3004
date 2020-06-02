#include "./Program.hpp"
#include "./Utilities.hpp"
#include "AlgorithmsForVisuals/Genetic.hpp"

#include <SFML/Graphics.hpp>
#include <array>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <fmt/format.hpp>

#if 0
#define FILE "test.txt"
#else
#define FILE "cities.txt"
#endif

sf::Color getColor(size_t current, size_t max)
{
	return sf::Color(255, std::lerp(255.f, 0.f, (current + 0.f) / max), 248);
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

	std::array<uint16_t, 48> best_index_array {0,  8,  37, 30, 43, 17, 6,  27, 35, 29, 5,  36,
											   18, 26, 42, 16, 45, 32, 14, 11, 10, 22, 13, 24,
											   12, 20, 46, 19, 39, 2,  21, 15, 40, 33, 28, 4,
											   47, 38, 31, 23, 9,  41, 25, 3,  34, 44, 1,  7};

	char buff[16U];
	std::puts("Start Program? Yes/No");
	std::scanf("%16s", buff);

	if(std::strcmp(buff, "no") == 0 || std::strcmp(buff, "No") == 0 ||
	   std::strcmp(buff, "NO") == 0 || *buff == 'N' || *buff == 'n')
		return 1;

	Genetic<uint16_t, cities.size(), 1024ULL> ga(0.015f);
	while(program.window().isOpen())
	{
		// Change vertexArray here to affect the results;
		const float shortest_distance = ga.exec(index_array, best_index_array);

		size_t count = 0ULL;
		for(const size_t i: index_array)
		{
			program.vertexArray()[count].position.x = program.cities()[i].windowPosition().x;
			program.vertexArray()[count].position.y =
				program.window().getSize().y - program.cities()[i].windowPosition().y;
			//			program.vertexArray()[count].color = getColor(count, index_array.size());
			program.vertexArray()[count].color = sf::Color(208, 208, 208, 60);
			++count;
		}
		auto& last = program.vertexArray()[program.vertexArray().getVertexCount() - 1ULL];
		last.position.x = program.cities()[0].windowPosition().x;
		last.position.y = program.window().getSize().y - program.cities()[0].windowPosition().y;
		last.color = sf::Color(208, 208, 208, 60);

		count = 0ULL;

		for(const size_t i: best_index_array)
		{
			program.vertexArray2()[count].position.x = program.cities()[i].windowPosition().x;
			program.vertexArray2()[count].position.y =
				program.window().getSize().y - program.cities()[i].windowPosition().y;
			program.vertexArray2()[count].color = sf::Color::Magenta;
			++count;
		}
		auto& last_best = program.vertexArray2()[program.vertexArray2().getVertexCount() - 1ULL];
		last_best.position.x = program.cities()[0].windowPosition().x;
		last_best.position.y =
			program.window().getSize().y - program.cities()[0].windowPosition().y;
		last_best.color = sf::Color::Magenta;

		if(!program.run())
			break;
	}

	fmt::print("Thanks! Hope you enjoyed our program ^_^\n");

	return 0;
}
