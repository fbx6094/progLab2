#ifndef SVGDOCUMENT_H
#define SVGDOCUMENT_H

#include "SVGElement.h"
#include <vector>
#include <memory>
#include <string>

class SVGDocument {
private:
    double width = 800.0;
    double height = 600.0;
    double viewBoxMinX = 0.0;
    double viewBoxMinY = 0.0;
    double viewBoxWidth = 800.0;
    double viewBoxHeight = 600.0;
    std::vector<std::string> defs;
    std::vector<std::unique_ptr<SVGElement>> elements;

public:
    SVGDocument() = default;
    SVGDocument(const SVGDocument& other);
    SVGDocument& operator=(const SVGDocument& other);
    SVGDocument(SVGDocument&& other) noexcept = default;
    SVGDocument& operator=(SVGDocument&& other) noexcept = default;

    void setCanvas(double w, double h);
    void setViewBox(double minX, double minY, double w, double h);
    void addDef(const std::string& defXml);
    void addElement(std::unique_ptr<SVGElement> element);

    double getWidth() const;
    double getHeight() const;
    double getViewBoxMinX() const;
    double getViewBoxMinY() const;
    double getViewBoxWidth() const;
    double getViewBoxHeight() const;

    std::string toString() const;
    bool saveToFile(const std::string& filename) const;
};

#endif
