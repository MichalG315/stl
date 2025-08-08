#include "transform-containers.hpp"
#include <algorithm>
#include <deque>
#include <list>
#include <map>
#include <string>

std::map<int, std::string> removeDuplicateAndTransformToMap(std::list<std::string> list, std::deque<int> deq) {
    std::map<int, std::string> result;

    list.sort();
    auto listItToRemove = std::unique(list.begin(), list.end());
    list.erase(listItToRemove, list.end());

    std::sort(deq.begin(), deq.end());
    auto deqItToRemove = std::unique(deq.begin(), deq.end());
    deq.erase(deqItToRemove, deq.end());

    auto listIt = list.begin();
    auto deqIt = deq.begin();
    while (listIt != list.end() || deqIt != deq.end()) {
        result[*deqIt] = *listIt;
        listIt++;
        deqIt++;
    }

    return result;
}