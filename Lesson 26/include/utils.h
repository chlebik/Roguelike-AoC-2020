#ifndef UTILS_H
#define UTILS_H

#include "level.h"
#include "monster.h"

void pathFind(Position start, Position end);
void pathfindingSeek(Monster *monster, Location *userLocation);
void pathfindingRandom(Monster *monster);

#endif
