#include "SVGDocument.h"
#include <fstream>
#include <sstream>

SVGDocument::SVGDocument(const SVGDocument& other)
    : width(other.width),
      height(other.height),
      viewBoxMinX(other.viewBoxMinX),
      viewBoxMinY(other.viewBoxMinY),
      viewBoxWidth(other.viewBoxWidth),
      viewBoxHeight(other.viewBoxHeight),
      defs(other.defs) {
    elements.reserve(other.elements.size());
    for (const auto& elem : other.elements) {
        if (elem) {
            elements.push_back(elem->clone());
        }
    }
}

SVGDocument& SVGDocument::operator=(const SVGDocument& other) {
    if (this != &other) {
        width = other.width;
        height = other.height;
        viewBoxMinX = other.viewBoxMinX;
        viewBoxMinY = other.viewBoxMinY;
        viewBoxWidth = other.viewBoxWidth;
        viewBoxHeight = other.viewBoxHeight;
        defs = other.defs;
        elements.clear();
        elements.reserve(other.elements.size());
        for (const auto& elem : other.elements) {
            if (elem) {
                elements.push_back(elem->clone());
            }
        }
    }
    return *this;
}

void SVGDocument::setCanvas(double w, double h) {
    width = w;
    height = h;
}

void SVGDocument::setViewBox(double minX, double minY, double w, double h) {
    viewBoxMinX = minX;
    viewBoxMinY = minY;
    viewBoxWidth = w;
    viewBoxHeight = h;
}

void SVGDocument::addDef(const std::string& defXml) {
    defs.push_back(defXml);
}

void SVGDocument::addElement(std::unique_ptr<SVGElement> element) {
    if (element) {
        elements.push_back(std::move(element));
    }
}

double SVGDocument::getWidth() const {
    return width;
}

double SVGDocument::getHeight() const {
    return height;
}

double SVGDocument::getViewBoxMinX() const {
    return viewBoxMinX;
}

double SVGDocument::getViewBoxMinY() const {
    return viewBoxMinY;
}

double SVGDocument::getViewBoxWidth() const {
    return viewBoxWidth;
}

double SVGDocument::getViewBoxHeight() const {
    return viewBoxHeight;
}

std::string SVGDocument::toString() const {
    std::ostringstream ss;
    ss << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";
    ss << "<svg xmlns=\"http://www.w3.org/2000/svg\" width=\"" << width
       << "\" height=\"" << height << "\" viewBox=\""
       << viewBoxMinX << " " << viewBoxMinY << " " << viewBoxWidth << " " << viewBoxHeight << "\">\n";

    if (!defs.empty()) {
        ss << "  <defs>\n";
        for (const auto& def : defs) {
            ss << "    " << def << "\n";
        }
        ss << "  </defs>\n";
    }

    for (const auto& elem : elements) {
        if (elem) {
            ss << elem->render(1);
        }
    }

    ss << "</svg>\n";
    return ss.str();
}

bool SVGDocument::saveToFile(const std::string& filename) const {
    std::ofstream out(filename);
    if (!out.is_open()) {
        return false;
    }
    out << toString();
    return out.good();
}
