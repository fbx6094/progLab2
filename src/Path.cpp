#include "Path.h"
#include <sstream>

Path& Path::moveTo(double x, double y) {
    std::ostringstream ss;
    if (!d.empty()) {
        ss << " ";
    }
    ss << "M " << x << " " << y;
    d += ss.str();
    return *this;
}

Path& Path::lineTo(double x, double y) {
    std::ostringstream ss;
    if (!d.empty()) {
        ss << " ";
    }
    ss << "L " << x << " " << y;
    d += ss.str();
    return *this;
}

Path& Path::cubicTo(double x1, double y1, double x2, double y2, double x3, double y3) {
    std::ostringstream ss;
    if (!d.empty()) {
        ss << " ";
    }
    ss << "C " << x1 << " " << y1 << ", " << x2 << " " << y2 << ", " << x3 << " " << y3;
    d += ss.str();
    return *this;
}

Path& Path::quadTo(double x1, double y1, double x2, double y2) {
    std::ostringstream ss;
    if (!d.empty()) {
        ss << " ";
    }
    ss << "Q " << x1 << " " << y1 << ", " << x2 << " " << y2;
    d += ss.str();
    return *this;
}

Path& Path::closePath() {
    if (!d.empty()) {
        d += " ";
    }
    d += "Z";
    return *this;
}

void Path::setStrokeDashArray(const std::string& val) {
    strokeDashArray = val;
}

void Path::setStrokeLineCap(const std::string& val) {
    strokeLineCap = val;
}

void Path::setStrokeLineJoin(const std::string& val) {
    strokeLineJoin = val;
}

const std::string& Path::getD() const {
    return d;
}

const std::string& Path::getStrokeDashArray() const {
    return strokeDashArray;
}

const std::string& Path::getStrokeLineCap() const {
    return strokeLineCap;
}

const std::string& Path::getStrokeLineJoin() const {
    return strokeLineJoin;
}

std::string Path::render(size_t indent) const {
    std::ostringstream ss;
    ss << makeIndent(indent) << "<path d=\"" << d << "\"";
    if (!strokeDashArray.empty()) {
        ss << " stroke-dasharray=\"" << strokeDashArray << "\"";
    }
    if (!strokeLineCap.empty()) {
        ss << " stroke-linecap=\"" << strokeLineCap << "\"";
    }
    if (!strokeLineJoin.empty()) {
        ss << " stroke-linejoin=\"" << strokeLineJoin << "\"";
    }
    ss << renderAttributes() << " />\n";
    return ss.str();
}

std::unique_ptr<SVGElement> Path::clone() const {
    return std::make_unique<Path>(*this);
}
