#include <rogue.h>


Level *createLevel(int level, int numberOfRooms, int numberOfMonsters)
{
    Level *newLevel = malloc(sizeof(Level));

    newLevel->levelNumber = level;
    newLevel->numberOfRooms = numberOfRooms;
    newLevel->numberOfMonsters = numberOfMonsters;

    // We setup all the rooms and connections on the screen
    newLevel->rooms = roomsSetup(numberOfRooms);

    // Monsters creation and drawing section
    createMonsters(newLevel, newLevel->rooms);
    drawMonsters(newLevel);

    // Put all the Location instances in the Level
    saveLevelLocations(newLevel);

    // We setup a player as a last thing - we put him on top of the existing dungeon
    newLevel->user = playerSetup();
    placePlayerInTheLevel(newLevel);

    return newLevel;
}

int placePlayerInTheLevel(Level *level)
{
    int roomToPlacePlayerIn = rand() % level->numberOfRooms;
    int proposedX, proposedY;

    while (1) {
        // We make sure that the player is not placed in a wall
        proposedX = level->rooms[roomToPlacePlayerIn]->position.x + (rand() % (level->rooms[roomToPlacePlayerIn]->width - 2)) + 1;
        proposedY = level->rooms[roomToPlacePlayerIn]->position.y + (rand() % (level->rooms[roomToPlacePlayerIn]->height - 2)) + 1;

        // We make sure that there's no monster on the chosen location
        if(isMonsterOnLocation(&level->locations[proposedY][proposedX], level->monsters) == FALSE) {
            break;
        }
    }

    level->user->currentLocation = &level->locations[proposedY][proposedX];
    level->user->previousLocation = &level->locations[proposedY][proposedX];

    return 0;
}

void drawMonsters(Level *level) {
    for(int i = 0; i < level->numberOfMonsters; i++) {
       mvprintw(level->monsters[i]->currentLocation->position.y, level->monsters[i]->currentLocation->position.x, level->monsters[i]->displaySign);
    }
}

void saveLevelLocations(Level *level)
{
    int x, y;
    Location **locations = malloc(sizeof(Location *) * 25);

    for (y = 0; y < 25; y++) {

        locations[y] = malloc(sizeof(Location) * 100);

        for (x = 0; x < 100; x++) {

            char value = *unctrl(mvinch(y, x));
            if(value == '.') {
                locations[y][x].displaySign = getDisplaySignForLocationType(FLOOR);
            }

            if(value == '#') {
                locations[y][x].displaySign = getDisplaySignForLocationType(WALL);
            }

            if(value == '+') {
                locations[y][x].displaySign = getDisplaySignForLocationType(DOOR);
            }

            if(value == ' ') {
                locations[y][x].displaySign = getDisplaySignForLocationType(EMPTY);
            }

            locations[y][x].position.y = y;
            locations[y][x].position.x = x;
        }
    }

    level->locations = locations;
}