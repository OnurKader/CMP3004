#include "Algorithms.hpp"

BaseAlgorithm::BaseAlgorithm(Program& program) : m_program(program) {}

Exhaustive::Exhaustive(Program& program) : BaseAlgorithm(program) {}

bool Exhaustive::exec()
{
	// TODO: Generate all possible combinations of Cities and go through them all, calculating the
	// total distance in the process
	return true;
}
