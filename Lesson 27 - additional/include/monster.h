#ifndef MONSTER_H
#define MONSTER_H

#include "level.h"
#include "room.h"

typedef struct Monster {
    char *displaySign;
    struct Location *currentLocation;
    int health;
    int attack;
    bool pathfinding;
    bool alive;
} Monster;

void moveMonsters(Level *level);
Monster **createMonsters(Level *level, struct Room **rooms);
Monster *createMonster();
Monster *createMonsterObject(char *displaySign, int health, int attack, int speed, int defence, bool pathfinding);
void placeMonsterInTheLevel(Monster *monster, struct Room room);
void drawMonsters(Level *level);
bool isMonsterOnLocation(Location *location, Monster **monsters);
void killMonster(Monster *monster);
Monster *getMonsterAt(Location *location, Monster **monsters);

#endif
