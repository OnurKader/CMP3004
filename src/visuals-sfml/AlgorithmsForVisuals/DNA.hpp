#pragma once

#include "City.hpp"
#include "Random.hpp"

#include <algorithm>
#include <array>
#include <cfloat>
#include <fmt/format.hpp>
#include <numeric>
#include <type_traits>

template<typename T, size_t S>
class DNA final
{
public:
	DNA() : m_fitness {}
	{
		std::iota(m_genes.begin(), m_genes.end(), 0U);
		std::shuffle(m_genes.begin(), m_genes.end(), s_def_random_engine);
	}

	DNA(const DNA& other) = default;
	DNA& operator=(const DNA& other) = default;

	float calculateFitness(const std::array<T, S>& target_city_order)
	{
		float score = 0.f;
		for(size_t i = 0ULL; i < m_genes.size(); ++i)
			if(m_genes[i] == target_city_order[i])
				++score;

		// FIXME: Instead of 1.f / ... get a more sensible value, maybe just look at the 2 furthest
		// cities and get the max distance from them
		score += 1.f / (std::pow(getDistance(), 2.f) + 1.f);

		return m_fitness = score / S;
	}

	T& gene(const size_t index = 0ULL) noexcept { return m_genes[index]; }
	const T& gene(const size_t index = 0ULL) const noexcept { return m_genes[index]; }

	std::array<T, S>& genes() noexcept { return m_genes; }
	const std::array<T, S>& genes() const noexcept { return m_genes; }

	float fitness() const noexcept { return m_fitness; }

	DNA crossover(const DNA& other)
	{
		DNA child_dna;
		child_dna.m_genes.fill(69U);

		const size_t first = randomInt(0UL, this->m_genes.size() - 2UL);
		const size_t last = randomInt(first + 1UL, this->m_genes.size() - 1UL);

		for(size_t i = first; i < last; ++i)
			child_dna.m_genes[i] = this->m_genes[i];

		for(size_t i = 0ULL; i < other.m_genes.size(); ++i)
			if(!child_dna.contains(other.m_genes[i]))
				for(size_t j = 0ULL; j < child_dna.m_genes.size(); ++j)
					if(child_dna.m_genes[j] == 69U)
					{
						child_dna.m_genes[j] = other.m_genes[i];
						break;
					}

		return child_dna;
	}

	void mutate(const float mutation_chance) noexcept
	{
		for(size_t i = 0ULL; i < m_genes.size(); ++i)
		{
			if(randomFloat(0.f, 1.f) < mutation_chance)
			{
				const size_t random_index = randomInt(0ULL, S - 1ULL);
				const size_t next_index = (random_index + 1ULL) % m_genes.size();
				std::swap(m_genes[random_index], m_genes[next_index]);
			}
		}
	}

	bool contains(const T val_to_search)
	{
		return (std::find(m_genes.cbegin(), m_genes.cend(), val_to_search) != m_genes.cend());
	}

	void printGenes() { fmt::print("{}\n", m_genes); }

	bool isShortestPath() const
	{
		const auto& [first, second] = std::mismatch(m_genes.cbegin(),
													m_genes.cend(),
													shortest_path_for_48.cbegin(),
													shortest_path_for_48.cend());
		return (first == m_genes.cend() || second == shortest_path_for_48.cend());
	}

	float getDistance() const { return getTotalDistanceOfCities(cities, m_genes); }

private:
	std::array<T, S> m_genes;
	float m_fitness;
};
