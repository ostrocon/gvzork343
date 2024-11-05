#ifndef NPC_H
#define NPC_H

#include <vector>
#include <string>
#include <iostream>

class NPC {
    private:
        std::string name;
        std::string description;
        int messageNumber;
        std::vector<std::string> messages;

    public:
        // Constructor with validation for name and description
        NPC(const std::string& name, const std::string& description, const std::vector<std::string>& messages);

        // Getters for name and description
        std::string getName() const;
        std::string getDescription() const;

        // Returns the current message and updates message Number for the next call
        std::string getMessage();

        // Overloaded output operator to print only the name of the NPC
        friend std::ostream& operator<<(std::ostream& os, const NPC& npc);
};

#endif // NPC_H

