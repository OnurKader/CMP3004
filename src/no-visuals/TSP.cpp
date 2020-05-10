#include "City.hpp"

#include <iostream>

int main()
{
	constexpr City first(0U, 0U);
	constexpr City second(9U, 40U);

	std::cout << first.dist(second) << '\n';

	return 0;
}
