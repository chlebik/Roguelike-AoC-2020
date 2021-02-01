#include <rogue.h>


Level *createLevel(int level, int numberOfRooms, int numberOfMonsters)
{
    Level *newLevel = malloc(sizeof(Level));

    newLevel->levelNumber = level;
    newLevel->numberOfRooms = numberOfRooms;
    newLevel->numberOfMonsters = numberOfMonsters;

    // We setup all the rooms and connections on the screen
    Room **rooms = roomsSetup(numberOfRooms);

    // Monsters creation and drawing section
    createMonsters(newLevel, rooms);
    drawMonsters(newLevel);

    // Put all the Location instances in the Level
    saveLevelLocations(newLevel);

    // We setup a player as a last thing - we put him on top of the existing dungeon
    newLevel->user = playerSetup();

    return newLevel;
}

void drawMonsters(Level *level) {
    for(int i = 0; i < level->numberOfMonsters; i++) {
       mvprintw(level->monsters[i]->currentLocation->position.y, level->monsters[i]->currentLocation->position.x, level->monsters[i]->displaySign);
    }
}

void saveLevelLocations(Level *level)
{
    int x, y;
    Location **locations  = malloc(sizeof(Location *) * 35);

    for (y = 0; y < 35; y++) {

        locations[y] = malloc(sizeof(Location) * 50);

        for (x = 0; x < 50; x++) {
            locations[y][x].displaySign = unctrl(mvinch(y, x));
            locations[y][x].position.y = y;
            locations[y][x].position.x = x;
        }
    }

    level->locations = locations;
}