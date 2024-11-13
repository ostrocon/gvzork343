#include "game.h"
#include "location.h"
#include "Item.h"
#include "NPC.h"
// This function creates the world, including locations, NPCs, and items.
void Game::createWorld() {
    // Define some example items
    Item rustySword("Rusty Sword", "An old and rusted sword, probably not very effective.", 0, 4.5f);
    Item healingPotion("Healing Potion", "A small vial of healing liquid.", 0, 0.5f);
    Item loafBread("Loaf of Bread", "A simple loaf of bread. It restores some energy.", 150, 1.0f);

    // Define some example NPCs
    std::vector<std::string> sageMessages = {
        "Welcome, adventurer!",
        "Knowledge is the key to success.",
        "Beware of the dangers that lie ahead."
    };
    NPC wanderingSage("Wandering Sage", "An old sage with many tales to tell.", sageMessages);

    // Create locations
    Location forest("Enchanted Forest", "A mysterious forest filled with ancient trees.");
    Location village("Quiet Village", "A small, peaceful village with friendly villagers.");
    Location cave("Dark Cave", "A cold, dark cave that echoes with strange sounds.");

    // Add NPCs and items to locations
    forest.addNPC(wanderingSage);
    forest.addItem(rustySword);
    
    village.addItem(loafBread);
    
    cave.addItem(healingPotion);

    // Connect locations (e.g., "north" of the village is the forest, etc.)
    village.addLocation("north", &forest);
    forest.addLocation("south", &village);
    forest.addLocation("east", &cave);
    cave.addLocation("west", &forest);

    // Add locations to the world list
    world.push_back(forest);
    world.push_back(village);
    world.push_back(cave);
}

