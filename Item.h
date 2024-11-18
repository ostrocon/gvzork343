#ifndef ITEM_H
#define ITEM_H

#include <string>

// Yash Hazari, Lucian Whitaker, Connor Ostrowski

class Item {
public:
    Item(std::string name, std::string description, int weight, int calories);
    std::string getName() const;
    std::string getDescription() const;
    int getWeight() const;
    int getCalories() const;

private:
    std::string name;
    std::string description;
    int weight;
    int calories;
};

#endif // ITEM_H

