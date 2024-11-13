#include "Location.h"

Location::Location(std::string name, std::string description)
    : name(name), description(description) {}

void Location::setNeighbor(const std::string& direction, Location* neighbor) {
    neighbors[direction] = neighbor;
}

Location* Location::getNeighbor(const std::string& direction) const {
    auto it = neighbors.find(direction);
    return it != neighbors.end() ? it->second : nullptr;
}

