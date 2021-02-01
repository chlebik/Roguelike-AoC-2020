#include <rogue.h>
#include <level.h>
#include <room.h>
#include <player.h>
#include <monster.h>



Level *createLevel(int level, int numberOfRooms, int numberOfMonsters)
{
    Level *newLevel = malloc(sizeof(Level));

    newLevel->levelNumber = level;
    newLevel->numberOfRooms = numberOfRooms;
    newLevel->numberOfMonsters = numberOfMonsters;

    // We setup all the rooms and connections on the screen
    newLevel->rooms = roomsSetup(numberOfRooms);

    // Put all the Location instances in the Level
    saveLevelLocations(newLevel);

    // Monsters creation
    newLevel->monsters = createMonsters(newLevel, newLevel->rooms);

    // We setup a player as a last thing - we put him on top of the existing dungeon
    newLevel->player = playerSetup();
    placePlayerInTheLevel(newLevel);

    return newLevel;
}

void placePlayerInTheLevel(Level *level)
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

    level->player->currentLocation = &level->locations[proposedY][proposedX];
}


void saveLevelLocations(Level *level)
{
    int x, y;
    Location **locations = malloc(sizeof(Location *) * MAX_HEIGHT);

    for (y = 0; y < MAX_HEIGHT; y++) {

        locations[y] = malloc(sizeof(Location) * MAX_WIDTH);

        for (x = 0; x < MAX_WIDTH; x++) {
            locations[y][x].displaySign = resolveDisplaySignFromChar(*unctrl(mvinch(y, x)));
            locations[y][x].position.y = y;
            locations[y][x].position.x = x;
        }
    }

    level->locations = locations;
}

void drawLevel(Level *level)
{
    // printing locations
    for (int y = 0; y < MAX_HEIGHT; y++) {
        for (int x = 0; x < MAX_WIDTH; x++) {
            mvprintw(y, x, level->locations[y][x].displaySign);
        }
    }

    drawMonsters(level);
    drawPlayer(*level->player);
}