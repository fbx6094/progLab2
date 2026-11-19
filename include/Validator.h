#ifndef VALIDATOR_H
#define VALIDATOR_H

#include <string>

class Validator {
public:
    static bool isValidColor(const std::string& color);
    static bool isValidDimension(double value);
    static bool isValidNonNegative(double value);
    static bool isValidAngle(double value);
    static bool isValidCoordinate(double value);
};

#endif
