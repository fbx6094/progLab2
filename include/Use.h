#ifndef USE_H
#define USE_H

#include "SVGElement.h"
#include <string>

class Use : public SVGElement {
private:
    std::string href = "";
    double x = 0.0;
    double y = 0.0;

public:
    Use() = default;
    Use(const std::string& href, double x = 0.0, double y = 0.0);

    const std::string& getHref() const;
    double getX() const;
    double getY() const;

    void setHref(const std::string& val);
    void setX(double val);
    void setY(double val);

    std::string render(size_t indent = 0) const override;
    std::unique_ptr<SVGElement> clone() const override;
};

#endif
