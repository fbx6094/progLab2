#include "SVGDocumentBuilder.h"

SVGDocumentBuilder& SVGDocumentBuilder::setCanvas(double width, double height) {
    doc.setCanvas(width, height);
    return *this;
}

SVGDocumentBuilder& SVGDocumentBuilder::setViewBox(double minX, double minY, double width, double height) {
    doc.setViewBox(minX, minY, width, height);
    return *this;
}

SVGDocumentBuilder& SVGDocumentBuilder::addDef(const std::string& defContent) {
    doc.addDef(defContent);
    return *this;
}

SVGDocumentBuilder& SVGDocumentBuilder::addElement(std::unique_ptr<SVGElement> element) {
    doc.addElement(std::move(element));
    return *this;
}

SVGDocument SVGDocumentBuilder::build() {
    return std::move(doc);
}
