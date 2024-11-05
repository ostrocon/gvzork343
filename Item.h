// Item.h
// Represents an item in the GV-themed Zork game
// Note: Parts of this code were generated with the assistance of ChatGPT

#ifndef ITEM_H
#define ITEM_H

#include <string>
#include <iostream>

class Item {
private:
    std::string name;
    std::string description;
    int calories;
    float weight;

public:
    // Constructor with validation for each parameter
    Item(const std::string& name, const std::string& description, int calories, float weight);

    // Getters for each data member
    std::string getName() const;
    std::string getDescription() const;
    int getCalories() const;
    float getWeight() const;

    // Overloaded output operator to print the item in the required format
    friend std::ostream& operator<<(std::ostream& os, const Item& item);
};

#endif // ITEM_H

