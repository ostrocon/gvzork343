// Game.h
// Main game class for GV-themed Zork game

#ifndef GAME_H
#define GAME_H

#include <map>
#include <vector>
#include <string>
#include "location.h"
#include "Item.h"
#include "NPC.h"

class Game {
private:
    std::map<std::string, void(*)(std::vector<std::string>)> commands;
    std::vector<Item> inventory;
    int currentWeight;
    std::vector<Location> world;
    Location* currentLocation;
    int elfCaloriesNeeded;
    bool inProgress;

    void createWorld();
    std::map<std::string, void(*)(std::vector<std::string>)> setupCommands();
    Location* randomLocation();

    // Game commands
    void showHelp(std::vector<std::string> args);
    void talk(std::vector<std::string> args);
    void meet(std::vector<std::string> args);
    void take(std::vector<std::string> args);
    void give(std::vector<std::string> args);
    void go(std::vector<std::string> args);
    void showItems(std::vector<std::string> args);
    void look(std::vector<std::string> args);
    void quit(std::vector<std::string> args);

public:
    Game();
    void play();
};

#endif // GAME_H

