#pragma once

#include "GeneratorTask.h"
#include "NumberQueue.h"
#include "RandomNumberGenerator.h"

class GeneratorDemo {
public:
    int run();

private:
    static constexpr int MinimumRandomValue = 1;
    static constexpr int MaximumRandomValue = 256;
    static constexpr int MinimumNumbersCount = 1;
    static constexpr int MaximumNumbersCount = 10000;

    static GeneratorTask generateNumbers(NumberQueue& queue, RandomNumberGenerator& generator, int numbersCount);

    void printIntroduction() const;

    void runGeneration(int numbersCount) const;

    void printQueueState(const NumberQueue& queue) const;
};
