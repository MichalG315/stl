#include "arithmeticAverage.hpp"
#include <cmath>
#include <numeric>
#include <vector>

double ArithmeticAverage(const std::vector<int>& vec1, const std::vector<int>& vec2) {
    double size1 = vec1.size();
    double size2 = vec2.size();
    auto sum1 = std::reduce(vec1.begin(), vec1.end(), 0);
    auto sum2 = std::reduce(vec2.begin(), vec2.end(), 0);

    return ((sum1 + sum2) / (size1 + size2));
}

double Distance(const std::vector<int>& vec1, const std::vector<int>& vec2) {
    double squaredSum = std::inner_product(vec1.begin(),
                                           vec1.end(),
                                           vec2.begin(),
                                           0,
                                           std::plus<double>(),
                                           [](const auto& lhs, const auto& rhs) {
                                               return std::pow(lhs - rhs, 2);
                                           });
    return std::sqrt(squaredSum);
}