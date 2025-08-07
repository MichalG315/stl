#include "palindrom.hpp"
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

bool is_palindrome(std::string text) {
    auto reversed = text;
    auto toRemoveText = std::remove_if(text.begin(), text.end(), [](const auto& c) { return !std::isalnum(c); });
    text.erase(toRemoveText, text.end());
    std::reverse(reversed.begin(), reversed.end());
    auto toRemoveReversed = std::remove_if(reversed.begin(), reversed.end(), [](const auto& c) { return !std::isalnum(c); });
    reversed.erase(toRemoveReversed, reversed.end());
    std::for_each(text.begin(), text.end(), [](char& c) { c = std::tolower(c); });
    std::for_each(reversed.begin(), reversed.end(), [](char& c) { c = std::tolower(c); });
    std::cout << text << "\n";
    std::cout << reversed << "\n";
    return std::equal(begin(text),
                      end(text),
                      begin(reversed),
                      end(reversed),
                      [](const auto& a, const auto& b) { return a == b; });
}