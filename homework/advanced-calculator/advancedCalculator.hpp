#pragma once
#include <string>

enum class ErrorCode {
    OK,
    BadCharacter,
    BadFormat,
    DivideBy0,
    SqrtOfNegativeNumber,
    ModuleOfNonIntegerValue
};

bool isValidNumberString(const std::string& s);
ErrorCode Separate(std::string& input, char& op, double* firstVal, double* secondVal);
bool isInteger(double n);
ErrorCode CheckErrors(char op, double firstVal, double secondVal);
bool hasInvalidAdjacentOperators(const std::string& input);
bool hasBadCharacter(const std::string& input);
ErrorCode process(std::string input, double* out);
