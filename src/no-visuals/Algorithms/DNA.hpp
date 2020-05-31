#pragma once

#include "City.hpp"
#include "Utilities.hpp"

#include <algorithm>
#include <array>
#include <numeric>
#include <random>
#include <type_traits>

static std::random_device s_random_device {};
static std::default_random_engine s_def_random_engine {s_random_device()};

template<typename T, size_t S>
bool isUnique(std::array<T, S> unsorted_array)
{
	std::sort(unsorted_array.begin(), unsorted_array.end());
	return std::adjacent_find(unsorted_array.begin(), unsorted_array.end()) == unsorted_array.end();
}

// Maybe I should do SFINAE
template<typename T>
T randomFromRange(const T min,
				  const T max) requires std::is_floating_point_v<T>	   // Qt Creator cannot
																	   // understand concepts yet
{
	static std::uniform_real_distribution<float> uniform_dist(min, max);
	return uniform_dist(s_def_random_engine);
}

template<typename T>
T randomFromRange(const T min, const T max) requires std::is_integral_v<T>
{
	static std::uniform_int_distribution<> uniform_dist(min, max);
	return uniform_dist(s_def_random_engine);
}

template<typename T, size_t S>
class DNA final
{
public:
	DNA() : m_fitness {0.f}
	{
		std::iota(m_genes.begin(), m_genes.end(), 0U);
		std::shuffle(m_genes.begin(), m_genes.end(), s_def_random_engine);
	}

	float calculateFitness(const std::array<T, S>& target_city_array)
	{
		size_t score = 0ULL;
		for(size_t i = 0ULL; i < S; ++i)
			if(m_genes[i] == target_city_array[i])
				++score;

		// Check if all genes are unique, if mutate somehow results in a 'set' of genes then we
		// should reward it? Well this also applies to the initial point of the genes
		const bool are_genes_all_unique = isUnique(m_genes);
		if(are_genes_all_unique)
			score += 2ULL;

		m_fitness = static_cast<float>(score) / S;
		return m_fitness;
	}

	T& gene(const size_t index = 0ULL) noexcept { return m_genes[index]; }
	const T& gene(const size_t index = 0ULL) const noexcept { return m_genes[index]; }

	DNA crossover(const DNA& other)
	{
		DNA child_dna;

		// TODO: Move the uniform distributor somewhere else?
		// Maybe a global templated function with the size so it returns what we want using the def
		// engine?
		const size_t first = randomFromRange(0UL, S - 2UL);
		const size_t last = randomFromRange(first + 1UL, S - 1UL);

		for(size_t i = first; i < last; ++i)
			child_dna.gene(i) = this->gene(i);

		for(size_t i = 0ULL; i < S; ++i)
		{
			const size_t index_from_other = other.gene(i);
			if(!child_dna.contains(index_from_other))
				child_dna.gene(i) = index_from_other;
		}

		return child_dna;
	}

	void mutate(const float mutation_chance) noexcept
	{
		for(size_t i = 0ULL; i < S; ++i)
		{
			if(randomFromRange(0.f, 1.f) < mutation_chance)
			{
				// TODO: Decide what to do here
				// Maybe don't do adjacent swaps, maybe two random cities swap, who knows
				const size_t random_index = randomFromRange(0UL, S - 1UL);
				const size_t next_index = (random_index) % S;
				std::swap(m_genes[random_index], m_genes[next_index]);
			}
		}
	}

	bool contains(const T val_to_search)
	{
		return (std::find(m_genes.cbegin(), m_genes.cend(), val_to_search) != m_genes.cend());
	}

private:
	std::array<T, S> m_genes;
	float m_fitness;
};
