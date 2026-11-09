#include "GeneratorDemo.h"

#include <exception>
#include <iostream>
#include <optional>

#include "InputReader.h"
#include "OddNumberWait.h"

int GeneratorDemo::run() {
    printIntroduction();

    InputReader reader(std::cin, std::cout);
    std::optional<int> numbersCount = reader.readIntegerInRange(
        "Enter how many numbers to generate: ", MinimumNumbersCount, MaximumNumbersCount);
    if (!numbersCount.has_value()) {
        std::cout << "\nError: input ended before a valid value was entered.\n";
        return 1;
    }

    std::cout << "\n";
    try {
        runGeneration(numbersCount.value());
    } catch (const std::exception& error) {
        std::cout << "Error: " << error.what() << "\n";
        return 1;
    }
    return 0;
}

GeneratorTask GeneratorDemo::generateNumbers(NumberQueue& queue, RandomNumberGenerator& generator, int numbersCount) {
    for (int index = 0; index < numbersCount; ++index) {
        int number = generator.next();
        queue.push(number);
        co_await OddNumberWait(number);
    }
}

void GeneratorDemo::printIntroduction() const {
    std::cout << "Coroutine generates random numbers from [" << MinimumRandomValue << ", "
              << MaximumRandomValue << "] and suspends on every odd number.\n";
    std::cout << "Input format: one integer from " << MinimumNumbersCount << " to "
              << MaximumNumbersCount << " on a single line.\n\n";
}

void GeneratorDemo::runGeneration(int numbersCount) const {
    NumberQueue queue;
    RandomNumberGenerator generator(MinimumRandomValue, MaximumRandomValue);
    GeneratorTask task = generateNumbers(queue, generator, numbersCount);

    int suspensionsCount = 0;
    while (!task.isFinished()) {
        task.resume();
        if (task.isFinished()) {
            break;
        }
        ++suspensionsCount;
        std::cout << "Suspension #" << suspensionsCount
                  << ": odd number " << queue.back() << " was generated\n";
        printQueueState(queue);
    }

    std::cout << "\nCoroutine finished after generating " << numbersCount << " numbers.\n";
    std::cout << "Total suspensions: " << suspensionsCount << "\n";
    printQueueState(queue);
}

void GeneratorDemo::printQueueState(const NumberQueue& queue) const {
    std::cout << "  Queue size: " << queue.size() << "\n";
    std::cout << "  Queue contents: ";
    queue.print(std::cout);
    std::cout << "\n";
}
