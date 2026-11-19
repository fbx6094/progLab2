#include "SVGElement.h"
#include <iomanip>

std::string SVGElement::makeIndent(size_t indent) {
    return std::string(indent * 2, ' ');
}

std::string SVGElement::renderAttributes() const {
    std::ostringstream ss;
    if (!id.empty()) {
        ss << " id=\"" << id << "\"";
    }
    if (!className.empty()) {
        ss << " class=\"" << className << "\"";
    }
    if (!fill.empty()) {
        ss << " fill=\"" << fill << "\"";
    }
    if (!stroke.empty()) {
        ss << " stroke=\"" << stroke << "\"";
    }
    if (hasStrokeWidth) {
        ss << " stroke-width=\"" << strokeWidth << "\"";
    }
    if (hasOpacity) {
        ss << " opacity=\"" << opacity << "\"";
    }
    if (!transform.empty()) {
        ss << " transform=\"" << transform << "\"";
    }
    return ss.str();
}

void SVGElement::setId(const std::string& val) {
    id = val;
}

void SVGElement::setClassName(const std::string& val) {
    className = val;
}

void SVGElement::setFill(const std::string& val) {
    fill = val;
}

void SVGElement::setStroke(const std::string& val) {
    stroke = val;
}

void SVGElement::setStrokeWidth(double val) {
    strokeWidth = val;
    hasStrokeWidth = true;
}

void SVGElement::setOpacity(double val) {
    opacity = val;
    hasOpacity = true;
}

void SVGElement::setTransform(const std::string& val) {
    transform = val;
}

const std::string& SVGElement::getId() const {
    return id;
}

const std::string& SVGElement::getClassName() const {
    return className;
}

const std::string& SVGElement::getFill() const {
    return fill;
}

const std::string& SVGElement::getStroke() const {
    return stroke;
}

double SVGElement::getStrokeWidth() const {
    return strokeWidth;
}

bool SVGElement::getHasStrokeWidth() const {
    return hasStrokeWidth;
}

double SVGElement::getOpacity() const {
    return opacity;
}

bool SVGElement::getHasOpacity() const {
    return hasOpacity;
}

const std::string& SVGElement::getTransform() const {
    return transform;
}
