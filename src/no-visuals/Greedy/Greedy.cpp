#include "Greedy.hpp"

template<size_t S>
std::array<size_t, S> greedy_algo(uint16_t** distance)
{
	size_t max = 0ULL;
	size_t i, j;
	std::array<bool, S> visited {true};
	std::array<size_t, S> path;
	std::array<uint16_t, S> minimum;
	std::array<uint16_t, S> min_index;
	size_t index;
	uint16_t min;
	size_t sum;
	size_t path_len, max_index;

	max = distance[0][1];
	for(i = 2; i < S; i++)
	{
		if(max < distance[0][i])
		{
			max = distance[0][i];
			index = i;
		}
	}

	visited[index] = true;
	path[0] = 0;
	path[1] = index;
	path_len = 2;
	while(path_len < S)
	{
		for(i = 0; i < S; i++)
		{
			if(!visited[i])
			{
				min = distance[path[0]][i] + distance[path[1]][i] - distance[path[0]][path[1]];
				index = 0;
				for(j = 1; j < path_len - 1; j++)
				{
					sum = distance[path[j]][i] + distance[path[j + 1]][i] -
						  distance[path[j]][path[j + 1]];
					if(sum < min)
					{
						min = sum;
						index = j;
					}
				}

				sum = distance[path[path_len - 1]][i] + distance[path[0]][i] -
					  distance[path[path_len - 1]][path[0]];
				if(sum < min)
				{
					min = sum;
					index = path_len - 1;
				}
				minimum[i] = min;
				min_index[i] = index;
			}
			else
			{
				minimum[i] = INT_MIN;
				min_index[i] = INT_MIN;
			}
		}

		max = minimum[0];
		max_index = 0;

		for(i = 1; i < S; i++)
		{
			if(minimum[i] > max)
			{
				max = minimum[i];
				max_index = i;
			}
		}

		for(i = path_len - 1; i >= (min_index[max_index] + 1); i--)
		{
			path[i + 1] = path[i];
		}
		path[i + 1] = max_index;
		visited[max_index] = true;
		++path_len;
	}

	return path;
}
