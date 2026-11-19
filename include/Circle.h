#ifndef CIRCLE_H
#define CIRCLE_H

#include "SVGElement.h"

class Circle : public SVGElement {
private:
    double cx = 0.0;
    double cy = 0.0;
    double r = 0.0;

public:
    Circle() = default;
    Circle(double cx, double cy, double r);

    double getCx() const;
    double getCy() const;
    double getR() const;

    void setCx(double val);
    void setCy(double val);
    void setR(double val);

    std::string render(size_t indent = 0) const override;
    std::unique_ptr<SVGElement> clone() const override;
};

#endif
