// Location.cpp
// Implementation of the Location class for the GV-themed Zork game

#include "location.h"
#include <stdexcept>
#include <sstream>

Location::Location(const std::string& name, const std::string& description) 
    : name(name), description(description), visited(false) {
    if (name.empty() || description.empty()) {
        throw std::invalid_argument("Location name and description cannot be blank.");
    }
}

std::map<std::string, Location*> Location::getLocations() const {
    return neighbors;
}

void Location::addLocation(const std::string& direction, Location* location) {
    if (direction.empty()) {
        throw std::invalid_argument("Direction cannot be blank.");
    }
    if (neighbors.find(direction) != neighbors.end()) {
        throw std::invalid_argument("This direction already has a location.");
    }
    neighbors[direction] = location;
}

void Location::addNPC(const NPC& npc) {
    npcs.push_back(npc);
}

std::vector<NPC> Location::getNpcs() const {
    return npcs;
}

void Location::addItem(const Item& item) {
    items.push_back(item);
}

std::vector<Item> Location::getItems() const {
    return items;
}

void Location::setVisited() {
    visited = true;
}

bool Location::getVisited() const {
    return visited;
}

std::ostream& operator<<(std::ostream& os, const Location& location) {
    os << location.name << " - " << location.description << std::endl;

    // Print NPCs
    os << "You see the following NPCs:" << std::endl;
    for (const auto& npc : location.npcs) {
        os << "- " << npc << std::endl;
    }

    // Print Items
    os << "You see the following Items:" << std::endl;
    for (const auto& item : location.items) {
        os << "- " << item << std::endl;
    }

    // Print Directions
    os << "You can go in the following Directions:" << std::endl;
    for (const auto& neighbor : location.neighbors) {
        os << "- " << neighbor.first << " - " 
           << neighbor.second->name 
           << (neighbor.second->getVisited() ? " (Visited)" : "") << std::endl;
    }
    return os;
}

