#pragma once

#include <random>

class RandomNumberGenerator {
public:
    RandomNumberGenerator(int minimumValue, int maximumValue);

    int next();

private:
    std::mt19937 engine;
    std::uniform_int_distribution<int> distribution;
};
