#include "compression.hpp"
#include <array>
#include <cstdint>
#include <vector>

std::vector<std::pair<uint8_t, uint8_t>> compressGrayscale(std::array<std::array<uint8_t, width>, height>& array) {
    uint8_t val = 0;
    uint8_t counter = 0;
    std::vector<std::pair<uint8_t, uint8_t>> output;

    for (auto& row : array) {
        for (auto it = row.begin(); it != row.end(); ++it) {
            if (it == row.begin()) {
                val = *it;
                counter = 1;
                continue;
            }

            if (val != *it) {
                output.push_back({val, counter});
                counter = 0;
            }

            val = *it;
            counter = counter + 1;
        }
        output.push_back({val, counter});
        counter = 0;
    }

    return output;
};

std::array<std::array<uint8_t, width>, height> decompressGrayscale(std::vector<std::pair<uint8_t, uint8_t>>& compressed) {
    std::array<std::array<uint8_t, width>, height> array;
    auto row = 0;
    auto column = 0;

    for (auto& pair : compressed) {
        for (size_t i = 0; i < pair.second; i++) {
            array[row][column] = pair.first;
            column++;
        }

        if (width <= column) {
            column = 0;
            row++;
        }
    }

    return array;
};
