#include "compression.hpp"
#include <algorithm>
#include <array>
#include <cstdint>
#include <numeric>
#include <vector>

std::vector<std::pair<uint8_t, uint8_t>> compressGrayscale(std::array<std::array<uint8_t, width>, height>& array) {
    uint8_t val = 0;
    uint8_t counter = 0;
    std::vector<std::pair<uint8_t, uint8_t>> output;

    for (auto& row : array) {
        uint8_t current = row[0];
        uint8_t counter = 1;

        std::accumulate(std::next(begin(row)),
                        end(row),
                        0,
                        [&](int, auto val) {
                            if (val == current) {
                                counter++;
                            } else {
                                output.emplace_back(current, counter);
                                current = val;
                                counter = 1;
                            }
                            return 0;
                        });
        output.emplace_back(current, counter);
    }

    return output;
};

std::array<std::array<uint8_t, width>, height> decompressGrayscale(std::vector<std::pair<uint8_t, uint8_t>>& compressed) {
    std::array<std::array<uint8_t, width>, height> array;
    auto row = 0;
    auto column = 0;

    std::for_each(compressed.begin(), compressed.end(), [&](const std::pair<uint8_t, uint8_t>& pair) {
        for (auto i = 0; i < pair.second; ++i) {
            array[row][column] = pair.first;
            column++;
        }
        if (column == width) {
            column = 0;
            row++;
        }
    });

    return array;
};