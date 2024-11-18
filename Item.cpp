#include "Item.h"

// Yash Hazari, Lucian Whitaker, Connor Ostrowski

Item::Item(std::string name, std::string description, int weight, int calories)
    : name(name), description(description), weight(weight), calories(calories) {}

std::string Item::getName() const {
    return name;
}

std::string Item::getDescription() const {
    return description;
}

int Item::getWeight() const {
    return weight;
}

int Item::getCalories() const {
    return calories;
}

