#pragma once

#include "Program.hpp"

#include <algorithm>

class BaseAlgorithm
{
	public:
	BaseAlgorithm(Program&);
	virtual bool exec() = 0;

	protected:
	Program& m_program;
};

class Exhaustive final : public BaseAlgorithm
{
	public:
	Exhaustive(Program&);

	protected:
	virtual bool exec() override;
};

using Lexicographical = Exhaustive;
