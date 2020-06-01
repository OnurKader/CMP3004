#pragma once

// FIXME: Replace all DNA<T, S> with a using statement to like RDNA or PDNA

#include "City.hpp"
#include "Population.hpp"
#include "Utilities.hpp"

#include <algorithm>
#include <array>
#include <fmt/format.hpp>
#include <numeric>
#include <vector>

template<typename T, size_t S, size_t P>
class Genetic final
{
public:
	Genetic() : m_population {}, m_shortest_distance {FLT_MAX} {};

	std::pair<float, std::array<T, S>> exec(const uint8_t log_level = 0U)
	{
		size_t iter_count = 0ULL;
		while(true)
		{
			m_population.calculateFitness();
			m_population.normalizeFitnesses();
			// fmt::print("\nFitnesses: {}\n", m_population.fitnesses());

			if(m_population.hasShortestPath())
			{
				fmt::print("Shortest Path Reached\n");
				break;
			}

			m_shortest_distance =
				std::min(m_shortest_distance, m_population.getShortestDistanceFromPopulation());

			fmt::print("Gen {} - shortest_dist: {}\n", iter_count, m_shortest_distance);

			nextGeneration();
			++iter_count;

			switch(log_level)
			{
				case 1U: break;
				default: break;
			}
		}

		return {};
	}

private:
	Population<T, S, P> m_population;
	float m_shortest_distance;

	// Should probably be in Population
	void nextGeneration() noexcept
	{
		Population<T, S, P> new_population;
		std::for_each(new_population.population().begin(),
					  new_population.population().end(),
					  [&](DNA<T, S>& dna) {
						  DNA<T, S> father = m_population.chooseParent();
						  DNA<T, S> mother = m_population.chooseParent();
						  DNA<T, S> child = father.crossover(mother);
						  child.mutate(0.015f);
						  dna = child;
					  });
		m_population = new_population;
	}
};
