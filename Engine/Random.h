#ifndef __ENGINE_RANDOM__
#define __ENGINE_RANDOM__

#include <ctime>
#include <random>

std::mt19937 globalRNG(static_cast<unsigned int>(std::time(0)));

#endif