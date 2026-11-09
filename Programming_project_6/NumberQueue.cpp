#include "NumberQueue.h"

#include <stdexcept>

void NumberQueue::push(int value) {
    values.push_back(value);
}

int NumberQueue::back() const {
    if (values.empty()) {
        throw std::out_of_range("Cannot read the last element of an empty queue");
    }
    return values.back();
}

std::size_t NumberQueue::size() const {
    return values.size();
}

void NumberQueue::print(std::ostream& output) const {
    output << "[";
    for (std::size_t index = 0; index < values.size(); ++index) {
        if (index > 0) {
            output << ", ";
        }
        output << values[index];
    }
    output << "]";
}
