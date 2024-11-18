#include <map>
#include <string>
#include <vector>
#include <memory>
#include "Item.h"
#include "NPC.h"

// Yash Hazari, Connor Ostrowski, Lucian Whitaker

class Location {
public:
    Location(std::string name, std::string description);
    void setNeighbor(const std::string& direction, Location* neighbor);
    Location* getNeighbor(const std::string& direction) const;
    void addItem(const Item& item);
    void addNPC(const NPC& npc);
    const std::vector<Item> getItems() const;
    std::vector<NPC> getNPCs() const;
    void setItems(const std::vector<Item>& newItems);

    std::string getName() const {
        return name;
    }

    std::string getDescription() const {
        return description;
    }

    std::map<std::string, Location*> getNeighbors() const {
        return neighbors;
    }

    void setVisited(bool state) {
        visited = state;
    }

    bool isVisited() const {
        return visited;
    }

private:
    std::string name;
    std::string description;
    std::map<std::string, Location*> neighbors;
    std::vector<Item> items;
    std::vector<NPC> npcs;
    bool visited = false;
};

