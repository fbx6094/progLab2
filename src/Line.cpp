#include "Line.h"
#include <sstream>

Line::Line(double x1, double y1, double x2, double y2)
    : x1(x1), y1(y1), x2(x2), y2(y2) {}

double Line::getX1() const {
    return x1;
}

double Line::getY1() const {
    return y1;
}

double Line::getX2() const {
    return x2;
}

double Line::getY2() const {
    return y2;
}

void Line::setX1(double val) {
    x1 = val;
}

void Line::setY1(double val) {
    y1 = val;
}

void Line::setX2(double val) {
    x2 = val;
}

void Line::setY2(double val) {
    y2 = val;
}

std::string Line::render(size_t indent) const {
    std::ostringstream ss;
    ss << makeIndent(indent) << "<line x1=\"" << x1 << "\" y1=\"" << y1
       << "\" x2=\"" << x2 << "\" y2=\"" << y2 << "\""
       << renderAttributes() << " />\n";
    return ss.str();
}

std::unique_ptr<SVGElement> Line::clone() const {
    return std::make_unique<Line>(*this);
}
