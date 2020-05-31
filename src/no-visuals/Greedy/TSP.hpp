#include <algorithm>
#include <array>
#include <climits>
#include <cmath>
#include <fstream>
#include <numeric>
#include <vector>

size_t findpathLength(int** distance);

std::array<size_t, 48> greedy_algo(uint16_t** distance, int dim);

struct Edge final
{
	int length;
};
