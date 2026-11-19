#ifndef LINE_H
#define LINE_H

#include "SVGElement.h"

class Line : public SVGElement {
private:
    double x1 = 0.0;
    double y1 = 0.0;
    double x2 = 0.0;
    double y2 = 0.0;

public:
    Line() = default;
    Line(double x1, double y1, double x2, double y2);

    double getX1() const;
    double getY1() const;
    double getX2() const;
    double getY2() const;

    void setX1(double val);
    void setY1(double val);
    void setX2(double val);
    void setY2(double val);

    std::string render(size_t indent = 0) const override;
    std::unique_ptr<SVGElement> clone() const override;
};

#endif
