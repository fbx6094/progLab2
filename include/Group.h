#ifndef GROUP_H
#define GROUP_H

#include "SVGElement.h"
#include <vector>
#include <memory>

class Group : public SVGElement {
private:
    std::vector<std::unique_ptr<SVGElement>> children;

public:
    Group() = default;
    Group(const Group& other);
    Group& operator=(const Group& other);
    Group(Group&& other) noexcept = default;
    Group& operator=(Group&& other) noexcept = default;

    void add(std::unique_ptr<SVGElement> child);
    size_t size() const;
    const SVGElement* get(size_t index) const;
    void clear();

    std::string render(size_t indent = 0) const override;
    std::unique_ptr<SVGElement> clone() const override;
};

#endif
