#include "Group.h"
#include <sstream>

Group::Group(const Group& other) : SVGElement(other) {
    children.reserve(other.children.size());
    for (const auto& child : other.children) {
        if (child) {
            children.push_back(child->clone());
        }
    }
}

Group& Group::operator=(const Group& other) {
    if (this != &other) {
        SVGElement::operator=(other);
        children.clear();
        children.reserve(other.children.size());
        for (const auto& child : other.children) {
            if (child) {
                children.push_back(child->clone());
            }
        }
    }
    return *this;
}

void Group::add(std::unique_ptr<SVGElement> child) {
    if (child) {
        children.push_back(std::move(child));
    }
}

size_t Group::size() const {
    return children.size();
}

const SVGElement* Group::get(size_t index) const {
    if (index < children.size()) {
        return children[index].get();
    }
    return nullptr;
}

void Group::clear() {
    children.clear();
}

std::string Group::render(size_t indent) const {
    std::ostringstream ss;
    ss << makeIndent(indent) << "<g" << renderAttributes() << ">\n";
    for (const auto& child : children) {
        if (child) {
            ss << child->render(indent + 1);
        }
    }
    ss << makeIndent(indent) << "</g>\n";
    return ss.str();
}

std::unique_ptr<SVGElement> Group::clone() const {
    return std::make_unique<Group>(*this);
}
