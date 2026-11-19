#ifndef RECT_H
#define RECT_H

#include "SVGElement.h"

class Rect : public SVGElement {
private:
    double x = 0.0;
    double y = 0.0;
    double width = 0.0;
    double height = 0.0;
    double rx = 0.0;
    double ry = 0.0;

public:
    Rect() = default;
    Rect(double x, double y, double width, double height, double rx = 0.0, double ry = 0.0);

    static Rect fromCenter(double cx, double cy, double width, double height, double rx = 0.0, double ry = 0.0);

    double getX() const;
    double getY() const;
    double getWidth() const;
    double getHeight() const;
    double getRx() const;
    double getRy() const;

    void setX(double val);
    void setY(double val);
    void setWidth(double val);
    void setHeight(double val);
    void setRx(double val);
    void setRy(double val);

    std::string render(size_t indent = 0) const override;
    std::unique_ptr<SVGElement> clone() const override;
};

#endif
