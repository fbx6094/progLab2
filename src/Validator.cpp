#include "Validator.h"
#include <algorithm>
#include <cctype>
#include <cmath>
#include <vector>

bool Validator::isValidColor(const std::string& color) {
    if (color.empty()) {
        return false;
    }
    if (color == "none") {
        return true;
    }
    if (color.rfind("url(#", 0) == 0 && color.back() == ')') {
        return color.length() > 6;
    }
    if (color.rfind("rgb(", 0) == 0 && color.back() == ')') {
        return true;
    }
    if (color.rfind("rgba(", 0) == 0 && color.back() == ')') {
        return true;
    }
    if (color[0] == '#') {
        size_t len = color.length();
        if (len != 4 && len != 5 && len != 7 && len != 9) {
            return false;
        }
        for (size_t i = 1; i < len; ++i) {
            if (!std::isxdigit(static_cast<unsigned char>(color[i]))) {
                return false;
            }
        }
        return true;
    }
    static const std::vector<std::string> namedColors = {
        "black", "white", "red", "green", "blue", "yellow", "cyan", "magenta",
        "gray", "grey", "orange", "purple", "pink", "brown", "gold", "silver",
        "navy", "teal", "lime", "maroon", "olive", "aqua", "fuchsia"
    };
    std::string lower = color;
    std::transform(lower.begin(), lower.end(), lower.begin(), [](unsigned char c) {
        return static_cast<char>(std::tolower(c));
    });
    for (const auto& name : namedColors) {
        if (lower == name) {
            return true;
        }
    }
    return false;
}

bool Validator::isValidDimension(double value) {
    return std::isfinite(value) && value > 0.0;
}

bool Validator::isValidNonNegative(double value) {
    return std::isfinite(value) && value >= 0.0;
}

bool Validator::isValidAngle(double value) {
    return std::isfinite(value);
}

bool Validator::isValidCoordinate(double value) {
    return std::isfinite(value);
}
