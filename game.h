#ifndef GAME_H
#define GAME_H

#include <map> 
#include <vector> 
#include <string>
#include "Location.h"

// Yash Hazari, Connor Ostrowski, Lucian Whitaker

// Declarations for classes used but not defined here
class Location;
class Item;
class NPC;

class Game {
public:
    Game();
    void play();
    std::map<std::string, void(Game::*)(std::vector<std::string>)> setupCommands();
    void createWorld();
    Location* randomLocation();
    void showHelp(std::vector<std::string> args);
    void talk(std::vector<std::string> args);
    void meet(std::vector<std::string> args);
    void take(std::vector<std::string> args);
    void give(std::vector<std::string> args);
    void go(std::vector<std::string> args);
    void showItems(std::vector<std::string> args);
    void look(std::vector<std::string> args);
    void quit(std::vector<std::string> args);
    // Custom commands
    void teleport(std::vector<std::string> args);
    void magic(std::vector<std::string> args);

private:
    Location* currentLocation;
    std::vector<Location> world;
    std::map<std::string, void(Game::*)(std::vector<std::string>)> commands;
    int currentWeight;
    int elfCaloriesNeeded;
    bool inProgress;
};

#endif // GAME_H

