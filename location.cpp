#include "Location.h"

Location::Location(std::string name, std::string description)
    : name(name), description(description) {}

void Location::setNeighbor(const std::string& direction, Location* neighbor) {
    neighbors[direction] = neighbor;
}

Location* Location::getNeighbor(const std::string& direction) const {
    auto it = neighbors.find(direction);
    if (it != neighbors.end()) {
        return it->second;
    } else {
        return nullptr;
    }
}

void Location::setItems(const std::vector<Item>& newItems) {
    items = newItems;  // Update the items with the modified list
}

void Location::addItem(const Item& item) {
    items.push_back(item);
}

void Location::addNPC(const NPC& npc) {
    npcs.push_back(npc);
}

const std::vector<Item> Location::getItems() const {
    return items;
}

std::vector<NPC> Location::getNPCs() const {
    return npcs;
}
