#ifndef ITEM_H
#define ITEM_H

#include <string>

class Item {
public:
    // Constructor now includes weight and calories
    Item(std::string name, std::string description, int weight, int calories);

    // Getters for name, description, weight, and calories
    std::string getName() const;
    std::string getDescription() const;
    int getWeight() const;
    int getCalories() const;

private:
    std::string name;
    std::string description;
    int weight;    // Weight of the item
    int calories;  // Calories associated with the item
};

#endif // ITEM_H

