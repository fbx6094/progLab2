#include "Circle.h"
#include <stdexcept>
#include <sstream>

Circle::Circle(double cx, double cy, double r) : cx(cx), cy(cy), r(r) {
    if (r <= 0.0) {
        throw std::invalid_argument("circle radius must be positive");
    }
}

double Circle::getCx() const {
    return cx;
}

double Circle::getCy() const {
    return cy;
}

double Circle::getR() const {
    return r;
}

void Circle::setCx(double val) {
    cx = val;
}

void Circle::setCy(double val) {
    cy = val;
}

void Circle::setR(double val) {
    if (val <= 0.0) {
        throw std::invalid_argument("circle radius must be positive");
    }
    r = val;
}

std::string Circle::render(size_t indent) const {
    std::ostringstream ss;
    ss << makeIndent(indent) << "<circle cx=\"" << cx << "\" cy=\"" << cy
       << "\" r=\"" << r << "\"" << renderAttributes() << " />\n";
    return ss.str();
}

std::unique_ptr<SVGElement> Circle::clone() const {
    return std::make_unique<Circle>(*this);
}
