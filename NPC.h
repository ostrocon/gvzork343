#ifndef NPC_H
#define NPC_H

#include <string>
#include <vector>
#include <stdexcept>
#include <iostream>

// Yash Hazari, Lucian Whitaker, Connor Ostrowski

class NPC {
public:
    NPC(std::string name, std::string description);
    std::string getName() const;
    std::string getDescription() const;
    std::string getMessage() const;
    // Overloaded stream operator
    friend std::ostream& operator<<(std::ostream& os, const NPC& npc);
    void addMessage(const std::string& message);

private:
    std::string name;
    std::string description;
    mutable int messageNumber = 0; // Message index
    std::vector<std::string> messages; // Messages vector
};

#endif

