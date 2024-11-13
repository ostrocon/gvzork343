#include <map>
#include <string>

class Location {
public:
    Location(std::string name, std::string description);
    
    // Set a neighboring location in a specific direction
    void setNeighbor(const std::string& direction, Location* neighbor);

    Location* getNeighbor(const std::string& direction) const;

private:
    std::string name;
    std::string description;
    std::map<std::string, Location*> neighbors;
};

