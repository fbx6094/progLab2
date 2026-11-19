#ifndef POLYLINE_H
#define POLYLINE_H

#include "SVGElement.h"
#include <vector>
#include <utility>

class Polyline : public SVGElement {
private:
    std::vector<std::pair<double, double>> points;

public:
    Polyline() = default;
    explicit Polyline(const std::vector<std::pair<double, double>>& pts);

    void addPoint(double x, double y);
    const std::vector<std::pair<double, double>>& getPoints() const;

    std::string render(size_t indent = 0) const override;
    std::unique_ptr<SVGElement> clone() const override;
};

#endif
