#pragma once

#include "City.hpp"
#include "Population.hpp"
#include "Utilities.hpp"

#include <algorithm>
#include <array>
#include <fmt/format.hpp>
#include <numeric>
#include <random>
#include <vector>

template<typename T, size_t S, size_t P>
class Genetic final
{
public:
	Genetic() {};

	std::pair<float, std::array<T, S>> exec(std::array<City, S>& city_array,
											const uint8_t log_level = 0U)
	{
		return {};
	}

private:
	Population<T, S, P> m_population;
};
