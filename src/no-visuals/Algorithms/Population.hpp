#pragma once

#include "DNA.hpp"

#include <array>

template<typename T, size_t S, size_t P>
class Population final
{
public:
	Population() : m_population {{}}, m_fitnesses {0.f} {}

	// I can get rid of m_fitnesses and just use m_population[i].fitness but hey
	void calculateFitness() noexcept
	{
		std::generate(m_fitnesses.begin(), m_fitnesses.end(), [&, i = 0ULL]() mutable {
			m_population[i].calculateFitness(shortest_path_for_48);
			return m_population[i++].fitness();
		});
	}

	void normalizeFitnesses() noexcept
	{
		const float total_fitness = std::accumulate(m_fitnesses.cbegin(), m_fitnesses.cend(), 0.f);

		std::for_each(m_fitnesses.begin(), m_fitnesses.end(), [total_fitness](float& fitness) {
			fitness /= total_fitness;
		});
	}

	DNA<T, S> chooseParent()
	{
		size_t index = 0ULL;
		float chance = randomFloat(0.f, 1.f);
		while(chance > 0.f)
			chance -= m_fitnesses[index++];

		return m_population[index - 1ULL];
	}

	std::array<DNA<T, S>, P>& population() { return m_population; }
	const std::array<DNA<T, S>, P>& population() const { return m_population; }

	std::array<float, S>& fitnesses() { return m_fitnesses; }
	const std::array<float, S>& fitnesses() const { return m_fitnesses; }

	bool hasShortestPath() const
	{
		for(const DNA<T, S>& dna: m_population)
			if(dna.isShortestPath())
				return true;

		return false;
	}

	float getShortestDistanceFromPopulation() const
	{
		float shortest_distance = FLT_MAX;

		for(const DNA<T, S>& dna: m_population)
		{
			const float dist = dna.getDistance();
			shortest_distance = std::min(dist, shortest_distance);
		}

		return shortest_distance;
	}

private:
	std::array<DNA<T, S>, P> m_population;
	std::array<float, S> m_fitnesses;

	//	DNA<T, S> m_best_dna_ever {};
	//	float m_best_fitness_ever {};
	//	DNA<T, S> m_current_best_dna {};
	//	float m_current_best_fitness {};
};
