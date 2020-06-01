#pragma once

#include "DNA.hpp"

#include <array>

template<typename T, size_t S, size_t P>
class Population final
{
public:
private:
	std::array<DNA<T, S>, P> m_population;
};
