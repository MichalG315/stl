#pragma once
#include <array>
#include <cstdint>
#include <vector>

constexpr std::size_t width = 32U;
constexpr std::size_t height = 32U;

std::vector<std::pair<uint8_t, uint8_t>> compressGrayscale(std::array<std::array<uint8_t, width>, height>& array);

std::array<std::array<uint8_t, width>, height> decompressGrayscale(std::vector<std::pair<uint8_t, uint8_t>>& vec);