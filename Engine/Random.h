#ifndef __ENGINE_RANDOM__
#define __ENGINE_RANDOM__

#include <algorithm>
#include <ctime>
#include <random>
namespace Random {
    std::mt19937 globalRNG(static_cast<unsigned int>(std::time(0)));
    std::uniform_real_distribution<double> doubleRNGDistribution(0.0, 1.0);
    // Generate a random number in range [0.0,1.0)
    double _double() { return doubleRNGDistribution(globalRNG); }

    std::uniform_int_distribution<int> intRNGDistribution(0, 232792560);

    // Generate a random number in range [0,232792560] (= 2^4 * 3^2 * 5 * 7 * 11 *
    // 13 * 17)
    int _int() { return intRNGDistribution(globalRNG); }

    // Generate a random player name
    std::string _name() {
        std::string alphaNumeric =
            "01233456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
        std::shuffle(alphaNumeric.begin(), alphaNumeric.end(), globalRNG);
        
        return alphaNumeric.substr(0, 10);
    }
}  // namespace Random
#endif