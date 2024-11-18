#include "NPC.h"

// Yash Hazari, Lucian Whitaker, Connor Ostrowski

NPC::NPC(std::string name, std::string description)
    : name(name), description(description) {}

std::string NPC::getName() const {
    return name;
}

std::string NPC::getDescription() const {
    return description;
}

std::string NPC::getMessage() const {
    if (messages.empty()) {
        return "This NPC has nothing to say.";
    }
    std::string currentMessage = messages[messageNumber];
    messageNumber = (messageNumber + 1) % messages.size();
    return currentMessage;
}

// Overloaded
std::ostream& operator<<(std::ostream& os, const NPC& npc) {
    os << npc.name;
    return os;
}

void NPC::addMessage(const std::string& message) {
    if (message.empty()) {
        throw std::invalid_argument("Message cannot be blank.");
    }
    messages.push_back(message);
}
