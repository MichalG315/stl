#include <iostream>
#include <string>
#include "advancedCalculator.hpp"

std::string to_string(ErrorCode ec) {
    switch (ec) {
    case ErrorCode::OK:
        return "OK\n";
    case ErrorCode::BadCharacter:
        return "BadCharacter\n";
    case ErrorCode::BadFormat:
        return "BadFormat\n";
    case ErrorCode::DivideBy0:
        return "DivideBy0\n";
    case ErrorCode::SqrtOfNegativeNumber:
        return "SqrtOfNegativeNumber\n";
    case ErrorCode::ModuleOfNonIntegerValue:
        return "ModuleOfNonIntegerValue\n";
    default:
        return "UnknownError\n";
    }
}

int main() {
    double* out = new double;
    std::string input;
    ErrorCode output;
    while (true) {
        std::cout << "Provide mathematical calculation like: <first operand> <operator> <second operand>, e.g. 5 + 3\nor provide q/Q to exit the program: \n";
        std::getline(std::cin, input);
        if (input == "Q" || input == "q") {
            return 0;
        }

        output = process(input, out);

        if (output == ErrorCode::OK) {
            std::cout << input << " = " << *out << "\n";
        } else {
            std::cout << "Error: " << to_string(output);
            return 0;
        }
    }
    return 0;
}
