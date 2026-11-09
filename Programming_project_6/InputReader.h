#pragma once

#include <istream>
#include <optional>
#include <ostream>
#include <string>

class InputReader {
public:
    InputReader(std::istream& inputStream, std::ostream& outputStream);

    std::optional<int> readIntegerInRange(const std::string& prompt, int minimumValue, int maximumValue);

private:
    static std::optional<int> parseInteger(const std::string& text);

    std::istream& input;
    std::ostream& output;
};
