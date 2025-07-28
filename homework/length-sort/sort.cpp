#include "sort.hpp"
#include <algorithm>
#include <deque>
#include <forward_list>
#include <string>

#include <algorithm>
#include <deque>
#include <forward_list>
#include <iostream>
#include <string>

bool comparator(std::string a, std::string b) {
    if (a.size() == b.size()) {
        auto it1 = a.begin();
        auto it2 = b.begin();
        for (; it1 != a.end(); ++it1, ++it2) {
            if (*it1 == *it2) {
                continue;
            } else {
                if (*it1 > *it2) {
                    return false;
                } else if (*it1 < *it2) {
                    return true;
                }
            }
        }
    } else {
        if (a.size() > b.size()) {
            return false;
        } else if (a.size() < b.size()) {
            return true;
        }
    }
}

std::deque<std::string> lengthSort(std::forward_list<std::string>& list) {
    std::deque<std::string> deq = {};

    list.sort(comparator);

    for (auto& elem : list) {
        deq.push_back(elem);
    }

    return deq;
}
