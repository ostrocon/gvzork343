#include "Game.h"
#include <iostream>
#include <sstream>
#include <ctime>
#include <iomanip> 
#include <algorithm>
#include <vector>
#include <string>

// Yash Hazari, Connor Ostrowski, Lucian Whitaker

// Set up game stats
Game::Game() : currentWeight(0), elfCaloriesNeeded(500), inProgress(true) {
    commands = setupCommands();
    createWorld();
    currentLocation = randomLocation();
}

// Set up commands
std::map<std::string, void(Game::*)(std::vector<std::string>)> Game::setupCommands() {
    std::map<std::string, void(Game::*)(std::vector<std::string>)> cmd;
    cmd["help"] = &Game::showHelp;
    cmd["talk"] = &Game::talk;
    cmd["meet"] = &Game::meet;
    cmd["take"] = &Game::take;
    cmd["give"] = &Game::give;
    cmd["go"] = &Game::go;
    cmd["show"] = &Game::showItems;
    cmd["look"] = &Game::look;
    cmd["quit"] = &Game::quit;
    // Add two custom commands here
    cmd["teleport"] = &Game::teleport;
    cmd["magic"] = &Game::magic;
    return cmd;
}

// Create map and world
void Game::createWorld() {
    // Create Locations
    Location kirkhoff("Kirkhoff", "The student center where there are restaraunts and study centers.");
    Location woods("Woods", "A dense forest filled with shadows.  The elf lives here, so feed him edible food to win.");
    Location padnos("Padnos", "A sciences hall where Chemistry classes are held.");
    Location mackinac("Mackinac", "A lecture building where many gen ed and computer science classes are held.");
    Location store("Laker Store", "A building that sells many very expensive GVSU merch and books for classes.");
    Location meadows("Meadows", "A clubhouse where golf merch is sold and people can relax before/after playing golf.");
    Location zumberge("Zumberge", "An administration building where Philly's office is.");
    Location blue("Blue Connection", "A building with the best food on campus.");
    
    // Create Items
    Item book("Book", "A dusty old book with faded letters.",5, 0);
    Item lantern("Lantern", "An oil lantern with a steady flame.",10, 0);
    Item beaker("Beaker", "A chemical beaker for storing liquid chemicals.",1,0);
    Item hoodie("Hoodie", "A sweatshirt with a hood that says GVSU.",2,0);
    Item candy("Candy", "A king size twix candy bar.",1,150);
    Item chips("Chips", "A party size bag of cool ranch doritos.",1,250);
    Item club("Club", "A 9 iron golf club.",5,0);
    Item lunch("Lunch", "A grilled cheese lunch meal.",2,1000);
    Item chair("Chair", "An office chair with wheels.",35,0);
    Item sandwhich("Sandwhich", "A sub from the blue connection with lettuce.",5,400);
    
    // Create NPCs
    NPC librarian("Librarian", "An elderly person with glasses who seems very knowledgeable.");
    NPC hunter("Hunter", "A rugged individual with a bow and quiver of arrows.");
    NPC professor("Professor", "Professor Woodring, a computer science wizard.");
    NPC attendant("Attendant", "A golf cart attendant.");
    NPC philly("Philly", "Philomena Mantella the President of GVSU.");
    
    // Add messages to the NPC
    librarian.addMessage("Hello, how can I help you?");
    librarian.addMessage("Books are a treasure trove of knowledge.");
    librarian.addMessage("Please return borrowed books on time!");

    hunter.addMessage("Feed the elf!");
    hunter.addMessage("Use the give command to feed the elf.");
    hunter.addMessage("If you don't bring me more food, I will hunt you instead.");

    professor.addMessage("Get your 343 project started early!");
    professor.addMessage("I am about to have a PhD.");
    professor.addMessage("Switzerland!!!");

    attendant.addMessage("Do you need your clubs cleaned?");
    attendant.addMessage("It is a great day for golf.");
    attendant.addMessage("Golf is better than fishing.");

    philly.addMessage("Anchor up!");
    philly.addMessage("See you at the game Saturday.");
    philly.addMessage("GVSU is the best school EVER!!");

    // Add Items and NPCs to Locations
    kirkhoff.addItem(book);
    kirkhoff.addNPC(librarian);

    woods.addItem(lantern);
    woods.addNPC(hunter);

    padnos.addItem(beaker);
    padnos.addNPC(philly);

    mackinac.addItem(candy);
    mackinac.addNPC(professor);

    store.addItem(hoodie);
    store.addItem(chips);
    
    meadows.addItem(club);
    meadows.addNPC(attendant);

    zumberge.addItem(lunch);
    zumberge.addItem(chair);

    blue.addItem(sandwhich);

    // Add Locations to the World
    world.push_back(kirkhoff);
    world.push_back(woods);
    world.push_back(padnos);
    world.push_back(mackinac);
    world.push_back(store);
    world.push_back(meadows);
    world.push_back(zumberge);
    world.push_back(blue);

    // Set Neighbors
    kirkhoff.setNeighbor("north", &padnos);
    kirkhoff.setNeighbor("west", &meadows);
    kirkhoff.setNeighbor("south", &blue);
    kirkhoff.setNeighbor("east", &zumberge);

    padnos.setNeighbor("north", &woods);
    padnos.setNeighbor("south", &kirkhoff);
    padnos.setNeighbor("west", &store);
    padnos.setNeighbor("east", &mackinac);

    woods.setNeighbor("south", &padnos);

    mackinac.setNeighbor("west", &padnos);
    mackinac.setNeighbor("south", &zumberge);
    
    store.setNeighbor("east", &padnos);
    store.setNeighbor("south", &meadows);

    meadows.setNeighbor("north", &store);
    meadows.setNeighbor("east", &kirkhoff);
    
    zumberge.setNeighbor("north", &mackinac);
    zumberge.setNeighbor("west", &kirkhoff);
    
    blue.setNeighbor("north", &kirkhoff);

}

// Pick random location
Location* Game::randomLocation() {
    int idx = std::rand() % world.size();
    return &world[idx];
}

// Function for game loop to play
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

// Function for help command
void Game::showHelp(std::vector<std::string> args) {
    std::cout << "Commands available:" << std::endl;
    for (const auto& cmd : commands) {
        std::cout << "- " << cmd.first << std::endl;
    }
    std::cout << "- magic" << std::endl;
    std::time_t now = std::time(nullptr);
    std::cout << "Current time: " << std::put_time(std::localtime(&now), "%H:%M:%S") << std::endl;
}

// Function to get message from NPC
void Game::talk(std::vector<std::string> args) {
    const auto& npcs = currentLocation->getNPCs();
    if (npcs.empty()) {
        std::cout << "There's no one here to talk to." << std::endl;
        return;
    }
    if (args.empty()) {
        std::cout << "Specify who you'd like to talk to. NPCs here: ";
        for (const auto& npc : npcs) {
            std::cout << npc.getName() << " ";
        }
        std::cout << std::endl;
        return;
    }
    std::string npcName = args[0];
    auto it = std::find_if(npcs.begin(), npcs.end(), [&npcName](const NPC& npc) {
        return npc.getName() == npcName;
    });
    if (it != npcs.end()) {
        std::cout << it->getName() << ": " << it->getMessage() << std::endl;
    } else {
        std::cout << "There's no one named " << npcName << " here." << std::endl;
    }
}

// Function to get NPC description
void Game::meet(std::vector<std::string> args) {
    const auto& npcs = currentLocation->getNPCs();
    if (npcs.empty()) {
        std::cout << "There's no one here to meet." << std::endl;
        return;
    }
    if (args.empty()) {
        const NPC& firstNPC = npcs.front();
        std::cout << "You meet " << firstNPC.getName() << ". " << firstNPC.getDescription() << std::endl;
        return;
    }
    std::string npcName = args[0];
    auto it = std::find_if(npcs.begin(), npcs.end(), [&npcName](const NPC& npc) {
        return npc.getName() == npcName;
    });
    if (it != npcs.end()) {
        std::cout << "You meet " << it->getName() << ". " << it->getDescription() << std::endl;
    } else {
        std::cout << "There's no one named " << npcName << " here." << std::endl;
    }
}

// Vector for items player has
std::vector<Item> playerInventory;

// Function to take item from location
void Game::take(std::vector<std::string> target) {
    std::vector<Item> items = currentLocation->getItems();
    if (target.empty()) {
        std::cout << "Specify what to take!" << std::endl;
        return;
    }
    std::string itemName = target[0];
    auto it = std::find_if(items.begin(), items.end(), [&itemName](const Item& item) {
        return item.getName() == itemName;
    });
    if (it != items.end()) {
        Item itemToTake = *it;
        items.erase(it);
        playerInventory.push_back(itemToTake);
        currentWeight += itemToTake.getWeight();
        std::cout << "You took the " << itemName << "." << std::endl;
    } else {
        std::cout << "No such item here!" << std::endl;
    }
    currentLocation->setItems(items);
}

// Function to give item to location
void Game::give(std::vector<std::string> target) {
    if (target.empty()) {
        std::cout << "You need to specify what item to give!" << std::endl;
        return;
    }
    std::string itemName = target[0];
    auto it = std::find_if(playerInventory.begin(), playerInventory.end(),
            [&itemName](const Item& item) {
            return item.getName() == itemName;
            });
    if (it == playerInventory.end()) {
        std::cout << "You don't have " << itemName << " in your inventory." << std::endl;
        return;
    }
    Item itemToGive = *it;
    playerInventory.erase(it);
    currentWeight -= itemToGive.getWeight();
    currentLocation->addItem(itemToGive);
    std::cout << "You gave " << itemName << " to the location." << std::endl;
    if (currentLocation->getName() == "Woods") {
        if (itemToGive.getCalories() > 0) {
            elfCaloriesNeeded -= itemToGive.getCalories();
            std::cout << "The elf consumes " << itemToGive.getCalories() << " calories. Remaining: " << elfCaloriesNeeded << " calories." << std::endl;
            if (elfCaloriesNeeded <= 0) {
                std::cout << "You win!  The elf is satisfies and the task is complete." << std::endl;
            }
        } else {
            currentLocation = randomLocation();
            std::cout << "The elf rejects your item as it is not edible and teleports you to a random location" << std::endl;
        }
    }
}

// Function to move to new location in direction specified
void Game::go(std::vector<std::string> target) {
    currentLocation->setVisited(true);
    if (currentWeight > 30) {
        std::cout << "You are carrying too much weight to move!" << std::endl;
        return;
    }
    if (target.empty()) {
        std::cout << "Specify a direction to move!" << std::endl;
        return;
    }
    std::string direction = target[0];
    Location* nextLocation = currentLocation->getNeighbor(direction);
    if (nextLocation) {
        currentLocation = nextLocation;
        std::cout << "You move " << direction << " to " << currentLocation->getName() << "." << std::endl;
    } else {
        std::cout << "You can't go that way!" << std::endl;
    }
}

// Function to show items in player's invenetory
void Game::showItems(std::vector<std::string> args) {
    if (playerInventory.empty()) {
        std::cout << "You are not carrying any items." << std::endl;
        return;
    }
    std::cout << "Items you are carrying:" << std::endl;
    for (const auto& item : playerInventory) {
        std::cout << "- " << item.getName() << " (" << item.getWeight() << " lbs)" << std::endl;
    }
    std::cout << "Total weight carried: " << currentWeight << " lbs" << std::endl;
}

// Function to get info about current location
void Game::look(std::vector<std::string> args) {
    if (currentLocation) {
        std::cout << "You are at: " << currentLocation->getName() << "\n";
        std::cout << currentLocation->getDescription() << "\n\n";
        std::cout << "Items here:\n";
        for (const auto& item : currentLocation->getItems()) {
            std::cout << "- " << item.getName() << ": " << item.getDescription() << "\n";
        }
        std::cout << "\nCharacters here:\n";
        for (const auto& npc : currentLocation->getNPCs()) {
            std::cout << "- " << npc.getName() << ": " << npc.getDescription() << "\n";
        }
        std::cout << "\nExits:\n";
        for (const auto& neighbor : currentLocation->getNeighbors()) {
            std::cout << "- " << neighbor.first << "\n";
        }
    } else {
        std::cout << "You are in an unknown location.\n";
    }
}

// Function to give up and terminate game
void Game::quit(std::vector<std::string> args) {
    inProgress = false;
    std::cout << "Quitting the game. Goodbye!" << std::endl;
}

// Custom command functions
// Function to teleport at anytime to some random location
void Game::teleport(std::vector<std::string> args) {
    currentLocation = randomLocation();
    std::cout << "You teleported to a new location!" << std::endl;
}

// Function to reduce calories needed by 500 instantly
void Game::magic(std::vector<std::string> args) {
    if (elfCaloriesNeeded > 0) {
        elfCaloriesNeeded -= 500;
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
