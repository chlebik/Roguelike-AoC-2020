#include <rogue.h>
#include <monster.h>
#include <room.h>
#include <utils.h>
#include <player.h>

#define GOBLIN_SIGN "g"
#define SPIDER_SIGN "S"

void drawMonster(Monster monster);


Monster **createMonsters(Level *level,  Room **rooms)
{
    int monstersCreated = 0;
    Monster **monsters = malloc(sizeof(Monster *) * level->numberOfMonsters);


    do {
        for(int i = 0; i < level->numberOfRooms; i++) {
            if((rand() % 2) == 0) {

                Monster *monster = createMonster();
                placeMonsterInTheLevel(monster, *rooms[i]);
                monsters[monstersCreated] = monster;

                monstersCreated += 1;
            }
        }
    } while(monstersCreated < level->numberOfMonsters);

    return monsters;
}

void placeMonsterInTheLevel(Monster *monster, Room room)
{
    Location *currentLocation = malloc(sizeof(Location));
    monster->currentLocation = malloc(sizeof(Location));

    currentLocation->position.x = (rand() % (room.width - 2)) + room.position.x + 1;
    currentLocation->position.y = (rand() % (room.height - 2)) + room.position.y + 1;
    currentLocation->displaySign = FLOOR_SIGN;

    monster->currentLocation = currentLocation;
}

Monster *createMonster(void) {
    if((rand() % 2)) {
        return createMonsterObject(GOBLIN_SIGN, 10, 1, 1, 2, FALSE);
    }
    return createMonsterObject(SPIDER_SIGN, 15, 4, 3, 1, FALSE);
}

Monster *createMonsterObject(char *displaySign, int health, int attack, int speed, int defence, bool pathfinding) {
    Monster *newMonster = malloc(sizeof(Monster));
    newMonster->displaySign = displaySign;
    newMonster->health = health;
    newMonster->attack = attack;
    newMonster->pathfinding = pathfinding;
    newMonster->alive = TRUE;

    return newMonster;
}

void moveMonsters(Level *level)
{
    for (int i = 0; i < level->numberOfMonsters; i++) {

        if (level->monsters[i]->pathfinding == TRUE) {
            pathfindingSeek(level->monsters[i], level);
        } else {
            pathfindingRandom(level->monsters[i], level);
        }

    }
}

void pathfindingRandom(Monster *monster, Level *level)
{
    int random = rand() % 5;

    switch (random) {

        case 0:
            if (canGoToLocation(level->locations[monster->currentLocation->position.y - 1][monster->currentLocation->position.x],
                                *level->player, level->monsters)) {
                monster->currentLocation->position.y -= 1;
            }
            break;
        case 1:
            if (canGoToLocation(level->locations[monster->currentLocation->position.y + 1][monster->currentLocation->position.x],
                                *level->player, level->monsters)) {
                monster->currentLocation->position.y += 1;
            }
            break;
        case 2:
            if (canGoToLocation(level->locations[monster->currentLocation->position.y][monster->currentLocation->position.x - 1],
                                *level->player, level->monsters)) {
                monster->currentLocation->position.x -= 1;
            }
            break;
        case 3:
            if (canGoToLocation(level->locations[monster->currentLocation->position.y][monster->currentLocation->position.x + 1],
                                *level->player, level->monsters)) {
                monster->currentLocation->position.x += 1;
            }
        case 4:
            break;
    }
}

void pathfindingSeek(Monster *monster, Level *level)
{
    Location userLocation = *level->player->currentLocation;

    if ((abs((monster->currentLocation->position.x - 1) - userLocation.position.x) < abs(monster->currentLocation->position.x - userLocation.position.x)) &&
            canGoToLocation(level->locations[monster->currentLocation->position.y][monster->currentLocation->position.x - 1],
                            *level->player, level->monsters)) {
        monster->currentLocation->position.x -= 1;
    } else if ((abs((monster->currentLocation->position.x + 1) - userLocation.position.x) < abs(monster->currentLocation->position.x - userLocation.position.x)) &&
            canGoToLocation(level->locations[monster->currentLocation->position.y][monster->currentLocation->position.x + 1],
                            *level->player, level->monsters)) {
        monster->currentLocation->position.x += 1;
    } else if ((abs((monster->currentLocation->position.y + 1) - userLocation.position.y) < abs(monster->currentLocation->position.y - userLocation.position.y)) &&
                canGoToLocation(level->locations[monster->currentLocation->position.y + 1][monster->currentLocation->position.x],
                            *level->player, level->monsters)) {
        monster->currentLocation->position.y += 1;
    } else if ((abs((monster->currentLocation->position.y - 1) - userLocation.position.y) < abs(monster->currentLocation->position.y - userLocation.position.y)) &&
                canGoToLocation(level->locations[monster->currentLocation->position.y - 1][monster->currentLocation->position.x],
                             *level->player, level->monsters)) {
        monster->currentLocation->position.y -= 1;
    }
}


bool isMonsterOnLocation(Location *location, Monster **monsters)
{
    for (int x = 0; x < NUMBER_OF_MONSTERS; x++) {

        if ((location->position.y == monsters[x]->currentLocation->position.y) &&
            (location->position.x == monsters[x]->currentLocation->position.x) &&
            monsters[x]->alive == TRUE) {
            return TRUE;
        }
    }

    return FALSE;
}

Monster *getMonsterAt(Location *location, Monster **monsters)
{
    for (int x = 0; x < NUMBER_OF_MONSTERS; x++) {
        if ((location->position.y == monsters[x]->currentLocation->position.y) &&
             (location->position.x == monsters[x]->currentLocation->position.x)) {
            return monsters[x];
        }
    }

    return NULL;
}

void killMonster(Monster *monster)
{
    monster->alive = FALSE;
}

void drawMonsters(Level *level) {
    for(int i = 0; i < level->numberOfMonsters; i++) {
        drawMonster(*level->monsters[i]);
    }
}

void drawMonster(Monster monster)
{
    if(monster.alive == TRUE) {
        mvprintw(monster.currentLocation->position.y, monster.currentLocation->position.x, monster.displaySign);
    }
}