// Location.h
// Represents a location in the GV-themed Zork game

#ifndef LOCATION_H
#define LOCATION_H

#include <string>
#include <map>
#include <vector>
#include "NPC.h"
#include "Item.h"

class Location {
private:
    std::string name;
    std::string description;
    bool visited;
    std::map<std::string, Location*> neighbors;
    std::vector<NPC> npcs;
    std::vector<Item> items;

public:
    // Constructor
    Location(const std::string& name, const std::string& description);

    // Neighbor management
    std::map<std::string, Location*> getLocations() const;
    void addLocation(const std::string& direction, Location* location);

    // NPC and Item management
    void addNPC(const NPC& npc);
    std::vector<NPC> getNpcs() const;
    void addItem(const Item& item);
    std::vector<Item> getItems() const;

    // Visitation management
    void setVisited();
    bool getVisited() const;

    // Output stream operator
    friend std::ostream& operator<<(std::ostream& os, const Location& location);
};

#endif // LOCATION_H

