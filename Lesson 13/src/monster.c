#include <rogue.h>

#define GOBLIN_SIGN "g"
#define SPIDER_SIGN "S"


void createMonsters(Level *level,  Room **rooms)
{
    int monstersCreated = 0;
    level->monsters = malloc(sizeof(Monster *) * level->numberOfMonsters);

    do {
        for(int i = 0; i < level->numberOfRooms; i++) {
            if((rand() % 2) == 0) {

                Monster *monster = createMonster();
                placeMonsterInTheLevel(monster, *rooms[i]);
                level->monsters[monstersCreated] = monster;

                monstersCreated += 1;
            }
        }
    } while(monstersCreated < level->numberOfMonsters);

}

void placeMonsterInTheLevel(Monster *monster, Room room)
{
    Location *currentLocation = malloc(sizeof(Location));
    monster->currentLocation = malloc(sizeof(Location));
    monster->previousLocation = malloc(sizeof(Location));

    currentLocation->position.x = (rand() % (room.width - 2)) + room.position.x + 1;
    currentLocation->position.y = (rand() % (room.height - 2)) + room.position.y + 1;
    currentLocation->displaySign = FLOOR_SIGN;

    monster->currentLocation = currentLocation;
    monster->previousLocation = currentLocation;
}

Monster *createMonster(void) {
    if((rand() % 2)) {
        return createMonsterObject(GOBLIN_SIGN, 10, 1, 1, 2, TRUE);
    }
    return createMonsterObject(SPIDER_SIGN, 15, 4, 3, 1, TRUE);
}

Monster *createMonsterObject(char *displaySign, int health, int attack, int speed, int defence, bool pathfinding) {
    Monster *newMonster = malloc(sizeof(Monster));
    newMonster->displaySign = displaySign;
    newMonster->health = health;
    newMonster->attack = attack;
    newMonster->speed = speed;
    newMonster->defence = defence;
    newMonster->pathfinding = pathfinding;

    return newMonster;
}

int moveMonsters(Level *level)
{
    for (int x = 0; x < level->numberOfMonsters; x++) {

        mvprintw(level->monsters[x]->previousLocation->position.y, level->monsters[x]->previousLocation->position.x, level->monsters[x]->previousLocation->displaySign);

        if (level->monsters[x]->pathfinding == TRUE) {
            pathfindingSeek(level->monsters[x], level->user->currentLocation);
        } else {
            // Here will be random pathfinding
        }

        // We redraw the location on which monster just stood
        mvprintw(level->monsters[x]->previousLocation->position.y, level->monsters[x]->previousLocation->position.x, level->monsters[x]->previousLocation->displaySign);
        // We draw monster in the new location
        mvprintw(level->monsters[x]->currentLocation->position.y, level->monsters[x]->currentLocation->position.x, level->monsters[x]->displaySign);
    }

}


int pathfindingSeek(Monster *monster, Location *userLocation)
{
    if ((abs((monster->currentLocation->position.x - 1) - userLocation->position.x) < abs(monster->currentLocation->position.x - userLocation->position.x)) &&
         (mvinch(monster->currentLocation->position.y, monster->currentLocation->position.x - 1)) == *FLOOR_SIGN) {
        monster->previousLocation = monster->currentLocation;
        monster->currentLocation->position.x -= 1;
        return 0;
    } else if ((abs((monster->currentLocation->position.x + 1) - userLocation->position.x) < abs(monster->currentLocation->position.x - userLocation->position.x)) &&
        (mvinch(monster->currentLocation->position.y, monster->currentLocation->position.x + 1)) == *FLOOR_SIGN) {
        monster->previousLocation = monster->currentLocation;
        monster->currentLocation->position.x += 1;
        return 0;
    } else if ((abs((monster->currentLocation->position.y + 1) - userLocation->position.y) < abs(monster->currentLocation->position.y - userLocation->position.y)) &&
        (mvinch(monster->currentLocation->position.y + 1, monster->currentLocation->position.x)) == *FLOOR_SIGN) {
        monster->previousLocation = monster->currentLocation;
        monster->currentLocation->position.y += 1;
        return 0;
    } else if ((abs((monster->currentLocation->position.y - 1) - userLocation->position.y) < abs(monster->currentLocation->position.y - userLocation->position.y)) &&
        (mvinch(monster->currentLocation->position.y - 1, monster->currentLocation->position.x))== *FLOOR_SIGN) {
        monster->previousLocation = monster->currentLocation;
        monster->currentLocation->position.y -= 1;
        return 0;
    }

    return 1;
}