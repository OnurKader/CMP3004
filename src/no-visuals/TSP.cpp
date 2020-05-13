#include "City.hpp"

#include <iostream>

template<typename T, size_t S>
void printArray(const std::array<T, S>& arr)
{
	std::cout << "[ ";
	for(size_t i = 0ULL; i < S - 1ULL; ++i)
		std::cout << arr[i] << ", ";
	std::cout << arr.back() << " ]\n";
}

int main()
{
	auto permutation_arrays = ctx::generateArrays<uint16_t, 8ULL>();
	std::for_each(permutation_arrays.begin(),
				  permutation_arrays.end(),
				  [index = 0ULL](auto&& arr) mutable { ctx::permutate(arr, index++); });
	for(const auto& arr: permutation_arrays)
		printArray(arr);

	for(size_t i = 0ULL; i < test_cities.size() - 1ULL; ++i)
	{
		std::cout << test_cities[i].dist(test_cities[i + 1ULL]) << '\n';
	}
	std::cout << test_cities.back().dist(test_cities.front()) << '\n';

	return 0;
}
