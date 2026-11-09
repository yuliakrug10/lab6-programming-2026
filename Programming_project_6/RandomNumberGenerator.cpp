#include "RandomNumberGenerator.h"

RandomNumberGenerator::RandomNumberGenerator(int minimumValue, int maximumValue)
    : engine(std::random_device{}()), distribution(minimumValue, maximumValue) {
}

int RandomNumberGenerator::next() {
    return distribution(engine);
}
