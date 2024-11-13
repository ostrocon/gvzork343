#ifndef NPC_H
#define NPC_H

#include <string>

class NPC {
public:
    NPC(std::string name, std::string description);

    std::string getName() const;
    std::string getDescription() const;

private:
    std::string name;
    std::string description;
};

#endif

