#include "NPC.h"

NPC::NPC(std::string name, std::string description)
    : name(name), description(description) {}

std::string NPC::getName() const {
    return name;
}

std::string NPC::getDescription() const {
    return description;
}

