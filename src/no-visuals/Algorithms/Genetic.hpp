#pragma once

// FIXME: Replace all DNA<T, S> with a using statement to like RDNA or PDNA

#include "City.hpp"
#include "Population.hpp"
#include "Utilities.hpp"

#include <algorithm>
#include <array>
#include <fmt/format.hpp>
#include <fmt/ostream.hpp>
#include <fstream>
#include <numeric>
#include <vector>

template<typename T, size_t S, size_t P>
class Genetic final
{
public:
	Genetic(const float mutation_rate) :
		m_population {}, m_shortest_distance {FLT_MAX}, m_mutation_rate {mutation_rate} {};

	std::pair<float, std::array<T, S>> exec(const uint8_t log_level = 0U)
	{
		std::ofstream out_file("ga_output");

		size_t iter_count = 0ULL;
		float prev_shortest_distance = m_shortest_distance;
		while(true)
		{
			m_population.calculateFitness();
			m_population.normalizeFitnesses();

			if(m_population.hasShortestPath())
			{
				fmt::print("Shortest Path Reached\n");
				break;
			}

			m_shortest_distance =
				std::min(m_shortest_distance, m_population.getShortestDistanceFromPopulation());

			switch(log_level)
			{
				case 1U:
					if(m_shortest_distance < prev_shortest_distance)
					{
						fmt::print(
							"Gen {:>7} - shortest_dist: {:.2f}\n", iter_count, m_shortest_distance);
						fmt::print(out_file,
								   "Gen {:>7} - shortest_dist: {:.2f}\n",
								   iter_count,
								   m_shortest_distance);
						prev_shortest_distance = m_shortest_distance;
					}
					break;
				case 2U: fmt::print("\nFitnesses: {}\n", m_population.fitnesses()); break;
				default: break;
			}

			nextGeneration();
			++iter_count;
		}

		return {};
	}

private:
	Population<T, S, P> m_population;
	float m_shortest_distance;
	float m_mutation_rate;

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
						  child.mutate(m_mutation_rate);
						  dna = child;
					  });
		m_population = new_population;
	}
};
