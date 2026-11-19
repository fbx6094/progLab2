#include "Rect.h"
#include <stdexcept>
#include <sstream>

Rect::Rect(double x, double y, double width, double height, double rx, double ry)
    : x(x), y(y), width(width), height(height), rx(rx), ry(ry) {
    if (width <= 0.0 || height <= 0.0) {
        throw std::invalid_argument("rectangle width and height must be positive");
    }
    if (rx < 0.0 || ry < 0.0) {
        throw std::invalid_argument("rectangle corner radii must be non-negative");
    }
}

Rect Rect::fromCenter(double cx, double cy, double width, double height, double rx, double ry) {
    double leftX = cx - width / 2.0;
    double topY = cy - height / 2.0;
    return Rect(leftX, topY, width, height, rx, ry);
}

double Rect::getX() const {
    return x;
}

double Rect::getY() const {
    return y;
}

double Rect::getWidth() const {
    return width;
}

double Rect::getHeight() const {
    return height;
}

double Rect::getRx() const {
    return rx;
}

double Rect::getRy() const {
    return ry;
}

void Rect::setX(double val) {
    x = val;
}

void Rect::setY(double val) {
    y = val;
}

void Rect::setWidth(double val) {
    if (val <= 0.0) {
        throw std::invalid_argument("rectangle width must be positive");
    }
    width = val;
}

void Rect::setHeight(double val) {
    if (val <= 0.0) {
        throw std::invalid_argument("rectangle height must be positive");
    }
    height = val;
}

void Rect::setRx(double val) {
    if (val < 0.0) {
        throw std::invalid_argument("rx must be non-negative");
    }
    rx = val;
}

void Rect::setRy(double val) {
    if (val < 0.0) {
        throw std::invalid_argument("ry must be non-negative");
    }
    ry = val;
}

std::string Rect::render(size_t indent) const {
    std::ostringstream ss;
    ss << makeIndent(indent) << "<rect x=\"" << x << "\" y=\"" << y
       << "\" width=\"" << width << "\" height=\"" << height << "\"";
    if (rx > 0.0) {
        ss << " rx=\"" << rx << "\"";
    }
    if (ry > 0.0) {
        ss << " ry=\"" << ry << "\"";
    }
    ss << renderAttributes() << " />\n";
    return ss.str();
}

std::unique_ptr<SVGElement> Rect::clone() const {
    return std::make_unique<Rect>(*this);
}
