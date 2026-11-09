#pragma once

#include <cstddef>
#include <deque>
#include <ostream>

class NumberQueue {
public:
    void push(int value);

    int back() const;

    std::size_t size() const;

    void print(std::ostream& output) const;

private:
    std::deque<int> values;
};
