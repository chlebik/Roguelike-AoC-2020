#include <rogue.h>


Level *createLevel(int level, int numberOfRooms)
{
    Level *newLevel = malloc(sizeof(Level));
    roomsSetup(numberOfRooms); // We setup all the rooms and connections on the screen

    newLevel->levelNumber = level;
    newLevel->numberOfRooms = numberOfRooms;
    newLevel->locations = saveLevelLocations();

    return newLevel;
}

Location **saveLevelLocations(void)
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

    return locations;
}