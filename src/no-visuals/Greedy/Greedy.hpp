#include <array>
#include <climits>
#include <cmath>
#include <fstream>

size_t findpathLength(int** distance);

template<size_t S>
std::array<size_t, S> greedy_algo(uint16_t** distance);

struct Edge final
{
	int length;
};
