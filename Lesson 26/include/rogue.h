#ifndef ROGUE_H
#define ROGUE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <curses.h>
#include <time.h>

#define ALLOWED_ROOM_LOCATIONS_NUMBER 4
#define NUMBER_OF_ROOMS 6
#define NUMBER_OF_MONSTERS 6
#define DEFAULT_LEVEL_NUMBER 1
#define MAX_WIDTH 100
#define MAX_HEIGHT 25
#define MAX_ITEMS 25


#define WALL_SIGN "#"
#define FLOOR_SIGN "."
#define PLAYER_SIGN "@"
#define DOOR_SIGN "+"
#define EMPTY_SIGN " "


enum Direction {DIRECTION_NW, DIRECTION_N, DIRECTION_NE, DIRECTION_W, DIRECTION_E, DIRECTION_SW, DIRECTION_S, DIRECTION_SE};
enum LocationType {FLOOR, WALL, DOOR, EMPTY};


#endif
