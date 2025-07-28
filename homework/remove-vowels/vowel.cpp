#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

std::vector<std::string> removeVowels(std::vector<std::string>& vec) {
    std::vector<char> vowels = {'a', 'e', 'i', 'o', 'u', 'y', 'A', 'E', 'I', 'O', 'U', 'Y'};

    for (auto& element : vec) {
        for (auto vowel : vowels) {
            if (element.find(vowel) != std::string::npos) {
                element.erase(std::remove(element.begin(), element.end(), vowel), element.end());
            }
        }
    }

    return vec;
}
