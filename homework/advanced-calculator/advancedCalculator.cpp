#include "advancedCalculator.hpp"
#include <algorithm>
#include <cmath>
#include <functional>
#include <iostream>
#include <map>
#include <string>

std::map<char, std::function<double(double, double)>> operations = {
    {'+', std::plus<double>()},
    {'-', std::minus<double>()},
    {'*', std::multiplies<double>()},
    {'/', std::divides<double>()},
    {'!', [](const double& lhs, const double&) { return lhs >= 0 ? tgamma(lhs + 1) : -tgamma(-lhs + 1); }},
    {'%', std::modulus<int>()},
    {'^', [](const double& base, const double& exp) { return pow(base, exp); }},
    {'$', [](const double& base, const double& exp) { return pow(base, 1.0 / exp); }}};

bool isValidNumberString(const std::string& s) {
    if (s.empty() || s[0] == '+') {
        return false;
    }

    size_t startIndex = (s[0] == '-') ? 1 : 0;
    if (startIndex == 1 && s.size() == 1) {
        return false;
    }

    int dotCount = 0;
    for (size_t i = startIndex; i < s.size(); ++i) {
        char c = s[i];
        if (c == ',') {
            return false;
        } else if (c == '.') {
            ++dotCount;
            if (dotCount > 1) {
                return false;
            }
        } else if (!isdigit(c)) {
            return false;
        }
    }
    return true;
}

ErrorCode Separate(std::string& input, char& op, double* firstVal, double* secondVal) {
    const std::string operators = "+-*/%^$!";
    auto factorialPos = std::find(input.begin(), input.end(), '!');
    if (factorialPos != input.end()) {
        op = '!';
        std::string firstNumber(input.begin(), factorialPos);

        if (!isValidNumberString(firstNumber) || std::next(factorialPos) != input.end()) {
            return ErrorCode::BadFormat;
        }

        try {
            *firstVal = std::stod(firstNumber);
        } catch (...) {
            return ErrorCode::BadFormat;
        }

        return ErrorCode::OK;
    }

    auto operatorPos = input.end();
    for (auto it = input.begin() + 1; it != input.end(); ++it) {
        if (operators.find(*it) != std::string::npos && !(*it == '-' && operators.find(*(it - 1)) != std::string::npos)) {
            operatorPos = it;
            break;
        }
    }

    if (operatorPos == input.end() || operatorPos == input.begin() || std::next(operatorPos) == input.end()) {
        return ErrorCode::BadFormat;
    }

    op = *operatorPos;
    std::string firstNumber(input.begin(), operatorPos);
    std::string secondNumber(operatorPos + 1, input.end());

    if (!isValidNumberString(firstNumber) || !isValidNumberString(secondNumber)) {
        return ErrorCode::BadFormat;
    }

    try {
        *firstVal = std::stod(firstNumber);
        *secondVal = std::stod(secondNumber);
    } catch (...) {
        return ErrorCode::BadFormat;
    }

    return ErrorCode::OK;
}

bool isInteger(double n) {
    return std::floor(n) == n;
}

ErrorCode CheckErrors(char op, double firstVal, double secondVal) {
    if (op == '/') {
        if (secondVal == 0) {
            return ErrorCode::DivideBy0;
        }
    }

    if (op == '%') {
        if (!isInteger(firstVal) || !isInteger(secondVal) || secondVal == 0) {
            return ErrorCode::ModuleOfNonIntegerValue;
        }
    }

    if (op == '$') {
        if (firstVal < 0) {
            return ErrorCode::SqrtOfNegativeNumber;
        }
    }

    return ErrorCode::OK;
}

bool hasInvalidAdjacentOperators(const std::string& input) {
    const std::string operators = "+-*/%^$";
    for (size_t i = 0; i + 1 < input.size(); ++i) {
        char cur = input[i];
        char next = input[i + 1];
        if (operators.find(cur) != std::string::npos && operators.find(next) != std::string::npos) {
            if (next == '-' && i + 2 < input.size() && (isdigit(input[i + 2]) || input[i + 2] == '.')) {
                continue;
            }
            return true;
        }
    }
    return false;
}

bool hasBadCharacter(const std::string& input) {
    const std::string allowedChars = "0123456789.+-*/%^$!,";
    for (char c : input) {
        if (allowedChars.find(c) == std::string::npos) {
            return true;
        }
    }
    return false;
}

ErrorCode process(std::string input, double* out) {
    char op = 0;
    double firstVal = 0.0;
    double secondVal = 0.0;

    input.erase(std::remove_if(input.begin(), input.end(), ::isspace), input.end());

    if (input.empty()) {
        return ErrorCode::BadFormat;
    }

    if (hasBadCharacter(input)) {
        return ErrorCode::BadCharacter;
    }

    if (hasInvalidAdjacentOperators(input)) {
        return ErrorCode::BadFormat;
    }

    ErrorCode err = Separate(input, op, &firstVal, &secondVal);
    if (err != ErrorCode::OK) {
        return err;
    }

    err = CheckErrors(op, firstVal, (op == '!') ? 0.0 : secondVal);
    if (err != ErrorCode::OK) {
        return err;
    }

    *out = operations.at(op)(firstVal, secondVal);
    return ErrorCode::OK;
}
