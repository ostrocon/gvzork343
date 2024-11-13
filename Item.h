#ifndef ITEM_H
#define ITEM_H

#include <string>

class Item {
public:
    Item(std::string name, std::string description);

    std::string getName() const;
    std::string getDescription() const;

private:
    std::string name;
    std::string description;
};

#endif

