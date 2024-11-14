#include "Game.h"
#include <iostream>
#include <sstream>
#include <ctime>
#include <iomanip>  // for time formatting
#include <algorithm> // for find_if

Game::Game() : currentWeight(0), elfCaloriesNeeded(500), inProgress(true) {
    commands = setupCommands();
    createWorld();
    currentLocation = randomLocation();
}

std::map<std::string, void(Game::*)(std::vector<std::string>)> Game::setupCommands() {
    std::map<std::string, void(Game::*)(std::vector<std::string>)> cmd;
    cmd["help"] = &Game::showHelp;
    cmd["talk"] = &Game::talk;
    cmd["meet"] = &Game::meet;
    cmd["take"] = &Game::take;
    cmd["give"] = &Game::give;
    cmd["go"] = &Game::go;
    cmd["show items"] = &Game::showItems;
    cmd["look"] = &Game::look;
    cmd["quit"] = &Game::quit;
    // Add two custom commands here
    cmd["teleport"] = &Game::teleport;
    cmd["magic"] = &Game::magic;
    return cmd;
}

void Game::createWorld() {
    // Create Locations
    Location kirkhoff("Kirkhoff Upstairs", "The student union. There are restaurants, a store, and places to congregate.");
    Location woods("Woods", "A dense forest filled with shadows.");
    
    // Create Items
    Item book("Old Book", "A dusty old book with faded letters.",10, 15);
    Item lantern("Lantern", "An oil lantern with a steady flame.",15, 10);
    
    // Create NPCs
    NPC librarian("Librarian", "An elderly person with glasses who seems very knowledgeable.");
    NPC hunter("Hunter", "A rugged individual with a bow and quiver of arrows.");
    
    // Add messages to the NPC
    librarian.addMessage("Hello, how can I help you?");
    librarian.addMessage("Books are a treasure trove of knowledge.");
    librarian.addMessage("Please return borrowed books on time!");

    // Add Items and NPCs to Locations
    kirkhoff.addItem(book);
    kirkhoff.addNPC(librarian);

    woods.addItem(lantern);
    woods.addNPC(hunter);

    // Add Locations to the World
    world.push_back(kirkhoff);
    world.push_back(woods);

    // Set Neighbors
    kirkhoff.setNeighbor("north", &woods);
    woods.setNeighbor("south", &kirkhoff);
}

Location* Game::randomLocation() {
    int idx = std::rand() % world.size();
    return &world[idx];
}

void Game::play() {
    std::cout << "Welcome to the GV-themed Zork game!" << std::endl;

    while (inProgress) {
        std::cout << "Enter command: ";
        std::string input;
        std::getline(std::cin, input);

        std::istringstream iss(input);
        std::vector<std::string> tokens;
        std::string token;
        while (iss >> token) {
            tokens.push_back(token);
        }

        if (tokens.empty()) continue;

        std::string command = tokens[0];
        tokens.erase(tokens.begin());

        auto it = commands.find(command);
        if (it != commands.end()) {
            (this->*it->second)(tokens);
        } else {
            std::cout << "Unknown command." << std::endl;
        }
    }

    if (elfCaloriesNeeded <= 0) {
        std::cout << "Congratulations! You have fed the elf enough calories!" << std::endl;
    } else {
        std::cout << "Game over. You failed to meet the elf's calorie needs." << std::endl;
    }
}

void Game::showHelp(std::vector<std::string> args) {
    std::cout << "Commands available:" << std::endl;
    for (const auto& cmd : commands) {
        std::cout << "- " << cmd.first << std::endl;
    }
    std::time_t now = std::time(nullptr);
    std::cout << "Current time: " << std::put_time(std::localtime(&now), "%H:%M:%S") << std::endl;
}

void Game::talk(std::vector<std::string> args) {
    // Get the NPCs from the current location
    const auto& npcs = currentLocation->getNPCs();
    if (npcs.empty()) {
        std::cout << "There's no one here to talk to." << std::endl;
        return;
    }

    if (args.empty()) {
        // If no name is provided, list NPCs present in the location
        std::cout << "Specify who you'd like to talk to. NPCs here: ";
        for (const auto& npc : npcs) {
            std::cout << npc.getName() << " ";
        }
        std::cout << std::endl;
        return;
    }

    // Attempt to find the NPC by name
    std::string npcName = args[0];
    auto it = std::find_if(npcs.begin(), npcs.end(), [&npcName](const NPC& npc) {
        return npc.getName() == npcName;
    });

    if (it != npcs.end()) {
        // Talk to the found NPC
        std::cout << it->getName() << ": " << it->getMessage() << std::endl;
    } else {
        // NPC not found in the location
        std::cout << "There's no one named " << npcName << " here." << std::endl;
    }
}

void Game::meet(std::vector<std::string> args) {
    // Get the NPCs from the current location
    const auto& npcs = currentLocation->getNPCs();
    if (npcs.empty()) {
        std::cout << "There's no one here to meet." << std::endl;
        return;
    }

    if (args.empty()) {
        // If no name is provided, meet the first NPC in the location
        const NPC& firstNPC = npcs.front();
        std::cout << "You meet " << firstNPC.getName() << ". " << firstNPC.getDescription() << std::endl;
        return;
    }

    // Attempt to find the NPC by name
    std::string npcName = args[0];
    auto it = std::find_if(npcs.begin(), npcs.end(), [&npcName](const NPC& npc) {
        return npc.getName() == npcName;
    });

    if (it != npcs.end()) {
        // NPC found, display their description
        std::cout << "You meet " << it->getName() << ". " << it->getDescription() << std::endl;
    } else {
        // NPC not found in the location
        std::cout << "There's no one named " << npcName << " here." << std::endl;
    }
}


void Game::take(std::vector<std::string> args) {
    // Implement logic to pick up items if present in the location
    std::cout << "You picked up an item." << std::endl;
}

void Game::give(std::vector<std::string> args) {
    // Implement logic for giving items to NPCs or leaving them
    std::cout << "You give an item." << std::endl;
}

void Game::go(std::vector<std::string> args) {
    // Implement movement logic based on available neighbors and current weight
    std::cout << "You move to a new location." << std::endl;
}

void Game::showItems(std::vector<std::string> args) {
    // Display items in player’s inventory and current weight
    std::cout << "You are carrying items." << std::endl;
}

void Game::look(std::vector<std::string> args) {
    if (currentLocation) {
        std::cout << "You are at: " << currentLocation->getName() << "\n";
        std::cout << currentLocation->getDescription() << "\n\n";

        // Display Items
        std::cout << "Items here:\n";
        for (const auto& item : currentLocation->getItems()) {
            std::cout << "- " << item.getName() << ": " << item.getDescription() << "\n";
        }

        // Display NPCs
        std::cout << "\nCharacters here:\n";
        for (const auto& npc : currentLocation->getNPCs()) {
            std::cout << "- " << npc.getName() << ": " << npc.getDescription() << "\n";
        }

        // Display Neighbors
        std::cout << "\nExits:\n";
        for (const auto& neighbor : currentLocation->getNeighbors()) {
            std::cout << "- " << neighbor.first << "\n";
        }
    } else {
        std::cout << "You are in an unknown location.\n";
    }
}

void Game::quit(std::vector<std::string> args) {
    inProgress = false;
    std::cout << "Quitting the game. Goodbye!" << std::endl;
}

// Custom command functions
void Game::teleport(std::vector<std::string> args) {
    currentLocation = randomLocation();
    std::cout << "You teleported to a new location!" << std::endl;
}

void Game::magic(std::vector<std::string> args) {
    if (elfCaloriesNeeded > 0) {
        elfCaloriesNeeded -= 500;
        if (elfCaloriesNeeded < 0) elfCaloriesNeeded = 0; // Ensure it doesn't go negative

        std::cout << "You cast a magical spell! Elf's calorie need is reduced by 500." << std::endl;
        std::cout << "Elf still needs " << elfCaloriesNeeded << " calories." << std::endl;

        if (elfCaloriesNeeded == 0) {
            std::cout << "Congratulations! The elf has enough calories!" << std::endl;
            inProgress = false; // End the game as a win condition
        }
    } else {
        std::cout << "The elf's calorie needs are already met. No magic needed!" << std::endl;
    }
}
