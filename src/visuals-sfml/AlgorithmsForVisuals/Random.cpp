#include "Random.hpp"

float zero_one()
{
	static std::uniform_real_distribution<float> uni_dist(0.f, 1.f);
	return uni_dist(s_def_random_engine);
}

size_t randomInt(const size_t min, const size_t max)
{
	const float result = zero_one() * (max - min) + min;
	return static_cast<size_t>(result);
}

float randomFloat(const float min, const float max) { return (max - min) * zero_one() + min; }
