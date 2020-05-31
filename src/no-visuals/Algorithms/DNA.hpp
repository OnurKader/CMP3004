#pragma once

#include "City.hpp"
#include "Utilities.hpp"

#include <algorithm>
#include <array>
#include <numeric>
#include <random>

static std::random_device s_random_device {};
static std::default_random_engine s_def_random_engine {s_random_device()};

template<typename T, size_t S>
bool isUnique(std::array<T, S> unsorted_array)
{
	std::sort(unsorted_array.begin(), unsorted_array.end());
	return std::adjacent_find(unsorted_array.begin(), unsorted_array.end()) == unsorted_array.end();
}

template<typename T>
requires(std::is_floating_point_v<T>) T randomFromRange(const T min, const T max)
{
	static std::uniform_real_distribution<float> uniform_dist(min, max);
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
		size_t gene_length =
			std::uniform_int_distribution<size_t>(0UL, S - 1UL)(s_def_random_engine);

		for(size_t i = 0ULL; i < S; ++i)
		{
			child_dna.gene(i) = [&] {
				if(i < gene_length)
					return this->gene(i);
				else
					return other.gene(i);
			}();
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
				const size_t random_index = 1;
				const size_t next_index = (random_index) % S;
				std::swap(m_genes.begin() + random_index, m_genes.begin() + next_index);
			}
		}
	}

private:
	std::array<T, S> m_genes;
	float m_fitness;
};
