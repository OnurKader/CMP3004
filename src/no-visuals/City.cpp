#include "City.hpp"

constexpr City::City(uint16_t _x, uint16_t _y) : position(_x, _y) {}

constexpr float City::dist(const City& other) const
{
	const auto _x = std::max(x, other.x) - std::min(x, other.x);
	const auto _y = std::max(y, other.y) - std::min(y, other.y);
	return std::sqrt((_x * _x) + (_y * _y));
}
