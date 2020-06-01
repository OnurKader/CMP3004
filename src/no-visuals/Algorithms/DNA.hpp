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

static constexpr auto& ga_city_array = cities;

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
