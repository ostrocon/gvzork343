#include <map>
#include <string>
#include <vector>
#include <memory>
#include "Item.h"
#include "NPC.h"

class Location {
public:
    Location(std::string name, std::string description);
    
    // Set a neighboring location in a specific direction
    void setNeighbor(const std::string& direction, Location* neighbor);

    Location* getNeighbor(const std::string& direction) const;
    
    void addItem(const Item& item);
    void addNPC(const NPC& npc);

    const std::vector<Item> getItems() const;
    std::vector<NPC> getNPCs() const;
    
    void setItems(const std::vector<Item>& newItems);  // Function to update items

    // In Location.h, add the following getter functions:

    // Getter for the name of the Location
    std::string getName() const {
        return name;
    }

    // Getter for the description of the Location
    std::string getDescription() const {
        return description;
    }

    // Getter for the neighbors (you may need to return the `neighbors` map)
    std::map<std::string, Location*> getNeighbors() const {
        return neighbors;
    }

private:
    std::string name;
    std::string description;
    std::map<std::string, Location*> neighbors;
    std::vector<Item> items;
    std::vector<NPC> npcs;
};

