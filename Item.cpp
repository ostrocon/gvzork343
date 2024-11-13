#include "Item.h"

Item::Item(std::string name, std::string description)
    : name(name), description(description) {}

std::string Item::getName() const {
    return name;
}

std::string Item::getDescription() const {
    return description;
}

