// Item.cpp
// Implementation of the Item class for GV-themed Zork game
// Note: Parts of this code were generated with the assistance of ChatGPT

#include "Item.h"
#include <stdexcept>
#include <sstream>

// Constructor with validation for each parameter
Item::Item(const std::string& name, const std::string& description, int calories, float weight) 
    : name(name), description(description), calories(calories), weight(weight) {
    
    // Validate name is not blank
    if (name.empty()) {
        throw std::invalid_argument("Item name cannot be blank.");
    }
    
    // Validate description is not blank
    if (description.empty()) {
        throw std::invalid_argument("Item description cannot be blank.");
    }
    
    // Validate calories is within range
    if (calories < 0 || calories > 1000) {
        throw std::invalid_argument("Calories must be between 0 and 1000.");
    }
    
    // Validate weight is within range
    if (weight < 0 || weight > 500) {
        throw std::invalid_argument("Weight must be between 0 and 500.");
    }
}

// Getter methods
std::string Item::getName() const { return name; }
std::string Item::getDescription() const { return description; }
int Item::getCalories() const { return calories; }
float Item::getWeight() const { return weight; }

// Overloaded output operator to format item information
std::ostream& operator<<(std::ostream& os, const Item& item) {
    os << item.name << " (" << item.calories << " calories) - " 
       << item.weight << " lb - " << item.description;
    return os;
}

