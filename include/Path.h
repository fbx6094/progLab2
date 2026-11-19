#ifndef PATH_H
#define PATH_H

#include "SVGElement.h"
#include <string>

class Path : public SVGElement {
private:
    std::string d = "";
    std::string strokeDashArray = "";
    std::string strokeLineCap = "";
    std::string strokeLineJoin = "";

public:
    Path() = default;

    Path& moveTo(double x, double y);
    Path& lineTo(double x, double y);
    Path& cubicTo(double x1, double y1, double x2, double y2, double x3, double y3);
    Path& quadTo(double x1, double y1, double x2, double y2);
    Path& closePath();

    void setStrokeDashArray(const std::string& val);
    void setStrokeLineCap(const std::string& val);
    void setStrokeLineJoin(const std::string& val);

    const std::string& getD() const;
    const std::string& getStrokeDashArray() const;
    const std::string& getStrokeLineCap() const;
    const std::string& getStrokeLineJoin() const;

    std::string render(size_t indent = 0) const override;
    std::unique_ptr<SVGElement> clone() const override;
};

#endif
