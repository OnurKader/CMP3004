#pragma once

#include "City.hpp"
#include "Random.hpp"

#include <algorithm>
#include <array>
#include <numeric>
#include <type_traits>

static constexpr auto& ga_city_array = cities;

template<typename T, size_t S>
class DNA final
{
public:
	DNA() : m_fitness {0.f}
	{
		std::iota(m_genes.begin(), m_genes.end(), 0U);
		std::shuffle(m_genes.begin(), m_genes.end(), s_def_random_engine);
	}

	DNA(DNA&& other) : m_genes(std::move(other.m_genes)), m_fitness(other.m_fitness) {}

	float calculateFitness(const std::array<T, S>& target_city_order)
	{
		float score = 0.f;
		for(size_t i = 0ULL; i < S; ++i)
			if(m_genes[i] == target_city_order[i])
				++score;

		// FIXME: Instead of 1.f / ... get a more sensible value, maybe just look at the 2 furthest
		// cities and get the max distance from them
		score +=
			1.f / (std::pow(getTotalDistanceOfCities(ga_city_array, target_city_order), 6.f) + 1.f);

		m_fitness = score / S;
		return m_fitness;
	}

	T& gene(const size_t index = 0ULL) noexcept { return m_genes[index]; }
	const T& gene(const size_t index = 0ULL) const noexcept { return m_genes[index]; }

	float fitness() const noexcept { return m_fitness; }

	DNA crossover(const DNA& other)
	{
		DNA child_dna;
		child_dna.m_genes.fill(0U);

		const size_t first = randomInt(0UL, S - 2UL);
		const size_t last = randomInt(first + 1UL, S - 1UL);

		fmt::print("first: {}, last: {}\n", first, last);

		for(size_t i = first; i < last; ++i)
			child_dna.gene(i) = this->gene(i);

		child_dna.printGenes();

		for(size_t i = 0ULL; i < S; ++i)
		{
			const size_t index_from_other = other.gene(i);
			if(!child_dna.contains(static_cast<T>(index_from_other)))
				child_dna.gene(i) = static_cast<T>(index_from_other);
		}

		child_dna.printGenes();

		return child_dna;
	}

	void mutate(const float mutation_chance) noexcept
	{
		for(size_t i = 0ULL; i < S; ++i)
		{
			if(randomFloat(0.f, 1.f) < mutation_chance)
			{
				// TODO: Decide what to do here
				// Maybe don't do adjacent swaps, maybe two random cities swap, who knows
				const size_t random_index = randomInt(0UL, S - 1UL);
				const size_t next_index = (random_index + 1ULL) % S;
				std::swap(m_genes[random_index], m_genes[next_index]);
			}
		}
	}

	bool contains(const T val_to_search)
	{
		return (std::find(m_genes.cbegin(), m_genes.cend(), val_to_search) != m_genes.cend());
	}

	void printGenes() { fmt::print("{}\n", m_genes); }

	bool isShortestPath() const { return m_genes == shortest_path_for_48; }

private:
	std::array<T, S> m_genes;
	float m_fitness;
};
