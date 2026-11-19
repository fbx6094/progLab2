#ifndef SVGDOCUMENTBUILDER_H
#define SVGDOCUMENTBUILDER_H

#include "SVGDocument.h"

class SVGDocumentBuilder {
private:
    SVGDocument doc;

public:
    SVGDocumentBuilder() = default;

    SVGDocumentBuilder& setCanvas(double width, double height);
    SVGDocumentBuilder& setViewBox(double minX, double minY, double width, double height);
    SVGDocumentBuilder& addDef(const std::string& defContent);
    SVGDocumentBuilder& addElement(std::unique_ptr<SVGElement> element);

    SVGDocument build();
};

#endif
