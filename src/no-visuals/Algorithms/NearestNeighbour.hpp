#pragma once

#include "City.hpp"
#include "Utilities.hpp"

#include <algorithm>
#include <array>
#include <cfloat>
#include <fmt/format.hpp>
#include <fstream>
#include <numeric>

template<typename T, size_t S>
class NearestNeighbour final
{
public:
	NearestNeighbour() {}

	std::pair<float, std::array<T, S>> exec(std::array<City, S>& city_array,
											const uint8_t log_level = 0U)
	{
	}

private:
	std::array<T, S> m_array;
};
