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
	Genetic(const float mutation_rate) :
		m_population {}, m_shortest_distance {FLT_MAX}, m_mutation_rate {mutation_rate} {};

	float exec(std::array<T, S>& array_to_fill, std::array<T, S>& best_one)
	{
		float prev_shortest_distance = m_shortest_distance;

		m_population.calculateFitness();
		m_population.normalizeFitnesses();

		m_shortest_distance =
			std::min(m_shortest_distance, m_population.getShortestDistanceFromPopulation());

		if(m_shortest_distance <= 33524.f)
		{
			fmt::print("Shortest Path Reached\n");

			return m_shortest_distance;
		}

		if(m_shortest_distance < prev_shortest_distance)
		{
			fmt::print("Gen {:>7} - shortest_dist: {:.2f}\n", m_iter_count, m_shortest_distance);

			prev_shortest_distance = m_shortest_distance;
			const auto shortest_path = m_population.getShortestPathFromPopulation();
			std::copy(shortest_path.cbegin(), shortest_path.cend(), best_one.begin());
		}

		const auto shortest_path = m_population.getShortestPathFromPopulation();
		std::copy(shortest_path.cbegin(), shortest_path.cend(), array_to_fill.begin());

		nextGeneration();
		++m_iter_count;

		return m_shortest_distance;
	}

private:
	Population<T, S, P> m_population;
	float m_shortest_distance;
	float m_mutation_rate;
	size_t m_iter_count = 0ULL;

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
