#include "Algorithms.hpp"
#include "Program.hpp"

#include <SFML/Graphics.hpp>
#include <array>
#include <fmt/format.h>

#ifndef ENABLE_SFML
constexpr bool enable_sfml = false;
#else
constexpr bool enable_sfml = true;
#endif

#if 1
#	define FILE "test.txt"
#else
#	define FILE "cities.txt"
#endif

constexpr std::array greyscale_table = {
	30U,  34U,	38U,  42U,	46U,  50U,	54U,  58U,	62U,  66U,	70U,  74U,	78U,  82U,	86U,  90U,
	94U,  98U,	102U, 106U, 110U, 114U, 118U, 122U, 126U, 130U, 134U, 138U, 142U, 146U, 150U, 154U,
	158U, 162U, 166U, 170U, 174U, 178U, 182U, 186U, 190U, 194U, 198U, 202U, 206U, 210U, 214U, 218U};

int main()
{
	if constexpr(enable_sfml)
	{
		Program program("../data/" FILE, 1440U, 920U);
		Lexicographical lex(program);
		// Use a function here before running and see the output on the window!
		//		bruteForce(program);
		while(program.window().isOpen())
		{
			for(size_t i = 0ULL; i < program.vertexArray().getVertexCount(); ++i)
			{
				program.vertexArray()[i].position = program.cities()[i].windowPosition();
				const auto grey = greyscale_table[i * 4U + 1U];
				program.vertexArray()[i].color = sf::Color(128U - grey, grey, 255U - grey);
			}

			if(!program.run())
				break;
		}
	}

	//	fmt::print("Thanks! Hope you enjoyed my program ^_^\n");

	return 0;
}
