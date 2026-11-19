#include "Polyline.h"
#include <sstream>

Polyline::Polyline(const std::vector<std::pair<double, double>>& pts) : points(pts) {}

void Polyline::addPoint(double x, double y) {
    points.emplace_back(x, y);
}

const std::vector<std::pair<double, double>>& Polyline::getPoints() const {
    return points;
}

std::string Polyline::render(size_t indent) const {
    std::ostringstream ss;
    ss << makeIndent(indent) << "<polyline points=\"";
    for (size_t i = 0; i < points.size(); ++i) {
        if (i > 0) {
            ss << " ";
        }
        ss << points[i].first << "," << points[i].second;
    }
    ss << "\"" << renderAttributes() << " />\n";
    return ss.str();
}

std::unique_ptr<SVGElement> Polyline::clone() const {
    return std::make_unique<Polyline>(*this);
}
