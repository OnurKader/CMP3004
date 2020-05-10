#include "Algorithms.hpp"

BaseAlgorithm::BaseAlgorithm(Program& program) : m_program(program) {}

Exhaustive::Exhaustive(Program& program) : BaseAlgorithm(program) {}

bool Exhaustive::exec()
{
	;
	return true;
}
