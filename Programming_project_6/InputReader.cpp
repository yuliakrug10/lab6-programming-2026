#include "InputReader.h"

#include <limits>
#include <sstream>

InputReader::InputReader(std::istream& inputStream, std::ostream& outputStream)
    : input(inputStream), output(outputStream) {
}

std::optional<int> InputReader::readIntegerInRange(const std::string& prompt, int minimumValue, int maximumValue) {
    while (true) {
        output << prompt;
        std::string line;
        if (!std::getline(input, line)) {
            return std::nullopt;
        }
        std::optional<int> parsedValue = parseInteger(line);
        if (!parsedValue.has_value()) {
            output << "Error: \"" << line << "\" is not a valid integer. Try again.\n";
            continue;
        }
        if (parsedValue.value() < minimumValue || parsedValue.value() > maximumValue) {
            output << "Error: the value must be between " << minimumValue
                   << " and " << maximumValue << ". Try again.\n";
            continue;
        }
        return parsedValue;
    }
}

std::optional<int> InputReader::parseInteger(const std::string& text) {
    std::istringstream stream(text);
    long long value = 0;
    if (!(stream >> value)) {
        return std::nullopt;
    }
    stream >> std::ws;
    if (!stream.eof()) {
        return std::nullopt;
    }
    if (value < std::numeric_limits<int>::min() || value > std::numeric_limits<int>::max()) {
        return std::nullopt;
    }
    return static_cast<int>(value);
}
