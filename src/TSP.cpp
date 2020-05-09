#include "Program.hpp"

#include <fmt/format.h>

#ifndef ENABLE_SFML
constexpr bool enable_sfml = false;
#else
constexpr bool enable_sfml = true;
#endif

int main()
{
	if constexpr(enable_sfml)
	{
		Program program("../data/test.txt", 1290U, 860U);
		program.run();
	}

	//	fmt::print("Thanks! Hope you enjoyed my program ^_^\n");

	return 0;
}
