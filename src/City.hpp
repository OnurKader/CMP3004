#pragma once

#include <SFML/System/Vector2.hpp>
#include <cstdint>

struct City final
{
	City(uint16_t x = 0U, uint16_t y = 0U, uint8_t t_index = 0U);

	bool operator<=>(const City&) const = default;

	float dist(const City&) const;
	static float dist(const City&, const City&);

	float distSqr(const City&) const;
	static float distSqr(const City&, const City&);

	sf::Vector2u position;
	uint8_t index;
};
