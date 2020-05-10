#include "City.hpp"

#include <iostream>

int main()
{
	std::cout << "OwO\n";
	constexpr City first {1U, 1U};
	constexpr City second {8U, 25U};

	std::cout << first.dist(second) << '\n';

	return 0;
}
