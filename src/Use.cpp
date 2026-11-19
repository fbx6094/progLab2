#include "Use.h"
#include <sstream>

Use::Use(const std::string& href, double x, double y)
    : href(href), x(x), y(y) {}

const std::string& Use::getHref() const {
    return href;
}

double Use::getX() const {
    return x;
}

double Use::getY() const {
    return y;
}

void Use::setHref(const std::string& val) {
    href = val;
}

void Use::setX(double val) {
    x = val;
}

void Use::setY(double val) {
    y = val;
}

std::string Use::render(size_t indent) const {
    std::ostringstream ss;
    ss << makeIndent(indent) << "<use href=\"" << href << "\" x=\"" << x << "\" y=\"" << y << "\"";
    ss << renderAttributes() << " />\n";
    return ss.str();
}

std::unique_ptr<SVGElement> Use::clone() const {
    return std::make_unique<Use>(*this);
}
