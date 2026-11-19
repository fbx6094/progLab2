#ifndef SVGELEMENT_H
#define SVGELEMENT_H

#include <string>
#include <memory>
#include <sstream>

class SVGElement {
protected:
    std::string id = "";
    std::string className = "";
    std::string fill = "";
    std::string stroke = "";
    double strokeWidth = 0.0;
    bool hasStrokeWidth = false;
    double opacity = 1.0;
    bool hasOpacity = false;
    std::string transform = "";

    std::string renderAttributes() const;
    static std::string makeIndent(size_t indent);

public:
    virtual ~SVGElement() = default;

    virtual std::string render(size_t indent = 0) const = 0;
    virtual std::unique_ptr<SVGElement> clone() const = 0;

    void setId(const std::string& val);
    void setClassName(const std::string& val);
    void setFill(const std::string& val);
    void setStroke(const std::string& val);
    void setStrokeWidth(double val);
    void setOpacity(double val);
    void setTransform(const std::string& val);

    const std::string& getId() const;
    const std::string& getClassName() const;
    const std::string& getFill() const;
    const std::string& getStroke() const;
    double getStrokeWidth() const;
    bool getHasStrokeWidth() const;
    double getOpacity() const;
    bool getHasOpacity() const;
    const std::string& getTransform() const;
};

#endif
