#include "City.hpp"

#include <cmath>

City::City(uint16_t x, uint16_t y, uint8_t t_index) : position(x, y), index(t_index) {}

float City::dist(const City& other) const
{
	const float x = static_cast<float>(position.x - other.position.x);
	const float y = static_cast<float>(position.y - other.position.y);
	return std::sqrt(x * x + y * y);
}

float City::dist(const City& first, const City& second)
{
	const float x = static_cast<float>(first.position.x - second.position.x);
	const float y = static_cast<float>(first.position.y - second.position.y);
	return std::sqrt(x * x + y * y);
}

float City::distSqr(const City& other) const
{
	const float x = static_cast<float>(position.x - other.position.x);
	const float y = static_cast<float>(position.y - other.position.y);
	return (x * x + y * y);
}

float City::distSqr(const City& first, const City& second)
{
	const float x = static_cast<float>(first.position.x - second.position.x);
	const float y = static_cast<float>(first.position.y - second.position.y);
	return (x * x + y * y);
}
