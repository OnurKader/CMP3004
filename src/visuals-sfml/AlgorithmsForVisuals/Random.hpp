#pragma once

#include <random>

static std::random_device s_random_device {};
static std::default_random_engine s_def_random_engine {s_random_device()};

float randomFloat(const float min, const float max);

size_t randomInt(const size_t min, const size_t max);
