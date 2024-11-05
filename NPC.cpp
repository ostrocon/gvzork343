#include "NPC.h"
#include <stdexcept>

// Constructor with validation for name and description
NPC::NPC(const std::string& name, const std::string& description, const std::vector<std::string>& messages)
    : name(name), description(description), messageNumber(0), messages(messages) {
    if (name.empty()) {
        throw std::invalid_argument("NPC name cannot be blank.");
    }
    if (description.empty()) {
        throw std::invalid_argument("NPC description cannot be blank.");
    }
}

// Getters for name and description
std::string NPC::getName() const { return name; }
std::string NPC::getDescription() const { return description; }

// getMessage() - Returns the current message and updates messageNumber
std::string NPC::getMessage() {
    if (messages.empty()) {
        return "(The NPC has nothing to say.)";
    }

    std::string currentMessage = messages[messageNumber];
    messageNumber = (messageNumber + 1) % messages.size();  // Cycle back to 0 after the last message
    return currentMessage;
}

// Overloaded output operator to display only the NPC's name
std::ostream& operator<<(std::ostream& os, const NPC& npc) {
    os << npc.name;
    return os;
}



