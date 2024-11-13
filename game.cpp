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
    // Create Locations, Items, and NPCs with descriptions

    Location kirkhoff("Kirkhoff Upstairs", 
                      "The student union. There are restaurants, a store, "
                      "and places to congregate.");
    // Add items and NPCs to kirkhoff...

    Location woods("Woods", "A dense forest filled with shadows.");
    // Add items and NPCs to woods...

    // Add more locations following this format
    world.push_back(kirkhoff);
    world.push_back(woods);
    // Add additional locations as needed...

    // Set up neighbors for locations
    kirkhoff.setNeighbor("north", &woods);
    woods.setNeighbor("south", &kirkhoff);
    // Set up additional neighbors for other locations as needed
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
    // Implement logic to interact with NPCs in the current location
    std::cout << "You try to talk, but there's no one here." << std::endl;
}

void Game::meet(std::vector<std::string> args) {
    // Check if NPC is present, if so, print description
    std::cout << "You meet someone interesting." << std::endl;
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
    // Print details about current location, items, NPCs, and exits
    std::cout << "Looking around, you see..." << std::endl;
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
    std::cout << "You cast a magical spell!" << std::endl;
}

