#include "Program.hpp"

#include <fmt/format.h>

#ifndef ENABLE_SFML
constexpr bool enable_sfml = false;
#else
constexpr bool enable_sfml = true;
#endif

#define DEBUG 1

#if DEBUG
#	define FILE "test.txt"
#else
#	define FILE "cities.txt"
#endif

int main()
{
	if constexpr(enable_sfml)
	{
		Program program("../data/" FILE, 1440U, 920U);
		// Use a function here before running and see the output on the window!
		//		bruteForce(program);
		while(program.window().isOpen())
		{
			if(!program.run())
				break;
		}
	}

	//	fmt::print("Thanks! Hope you enjoyed my program ^_^\n");

	return 0;
}
