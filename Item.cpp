#include "Item.h"

// Constructor to initialize all member variables
Item::Item(std::string name, std::string description, int weight, int calories)
    : name(name), description(description), weight(weight), calories(calories) {}

// Getter for name
std::string Item::getName() const {
    return name;
}

// Getter for description
std::string Item::getDescription() const {
    return description;
}

// Getter for weight
int Item::getWeight() const {
    return weight;
}

// Getter for calories
int Item::getCalories() const {
    return calories;
}

