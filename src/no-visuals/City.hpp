#pragma once

#include <array>
#include <cmath>
#include <cstdint>

struct Point final
{
	uint16_t x;
	uint16_t y;
};

struct City final
{
	constexpr City(uint16_t, uint16_t);

	constexpr float dist(const City& other) const;

	Point_u16 position;
	uint16_t& x = position.x;
	uint16_t& y = position.y;
};

// const static std::array<City, 48U> cities {(0, 0), {1, 1}};
