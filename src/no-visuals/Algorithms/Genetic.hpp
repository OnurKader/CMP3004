#pragma once

// FIXME: Replace all DNA<T, S> with a using statement to like RDNA or PDNA

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

	std::pair<float, std::array<T, S>> exec(const uint8_t log_level = 0U)
	{
		switch(log_level)
		{
			case 1U: fmt::print("Genetic is cool\n"); break;
			default: break;
		}

		return {};
	}

	void nextGeneration() noexcept
	{
		Population<T, S, P> new_population;
		std::for_each(new_population.population().begin(),
					  new_population.population().end(),
					  [&](DNA<T, S>& dna) {
						  DNA<T, S> father = m_population.chooseParent();
						  DNA<T, S> mother = m_population.chooseParent();
						  DNA<T, S> child = father.crossover(mother);
						  child.mutate(0.012f);
						  dna = child;
					  });
		m_population = new_population;
	}

private:
	Population<T, S, P> m_population;
};
