#include "NPC.h"
#include "Item.h"

int main() {
    std::vector<std::string> messages = {
        "Hello, traveler!",
        "Have you seen the mountains?",
        "Good luck on your journey."
    };
    
    try {
        Item rustyNail("Rusty Nail", "A rusty nail (I hope you've had a tetanus shot)", 0, 1.0f);
        std::cout << rustyNail << std::endl;
        std::cout << std::endl;
        std::cout << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    // Create an NPC object instead of using static method
    NPC wanderingSage("Wandering Sage", "A wise old sage with many tales to tell.", messages);

    std::cout << "NPC Name: " << wanderingSage.getName() << std::endl;
    std::cout << "Description: " << wanderingSage.getDescription() << std::endl;

    // Interacting with the NPC to get messages
    for (int i = 0; i < 5; i++) {
        std::cout << "NPC says: " << wanderingSage.getMessage() << std::endl;
    }

    return 0;
}

