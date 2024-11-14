#ifndef NPC_H
#define NPC_H

#include <string>
#include <vector>
#include <stdexcept>
#include <iostream>

class NPC {
public:
    NPC(std::string name, std::string description);

    std::string getName() const;
    std::string getDescription() const;
    
    // Getter for the current message, advancing the message number
    std::string getMessage() const;

    // Overloaded stream operator
    friend std::ostream& operator<<(std::ostream& os, const NPC& npc);

    // Add a message to the NPC
    void addMessage(const std::string& message);

private:
    std::string name;
    std::string description;
    mutable int messageNumber; // Tracks the current message index
    std::vector<std::string> messages; // Stores the NPC's messages
};

#endif

