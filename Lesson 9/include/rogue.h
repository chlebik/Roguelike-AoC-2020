#ifndef ROGUE_H
#define ROGUE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <curses.h>
#include <time.h>

#define ALLOWED_ROOM_LOCATIONS_NUMBER 4
#define WALL_SIGN "#"
#define FLOOR_SIGN "."
#define PLAYER_SIGN "@"
#define DOOR_SIGN "+"
#define EMPTY_SIGN " "


// Structs
typedef struct Position {
    int x;
    int y;
} Position;

typedef struct Location {
    Position position;
    const char *displaySign;
} Location;

typedef struct Room {
    Position position;
    int height;
    int width;
    Location locations[ALLOWED_ROOM_LOCATIONS_NUMBER];
} Room;

typedef struct Player {
    Position position;
    int health;
} Player;
//


// Enums
enum Direction {DIRECTION_NW, DIRECTION_N, DIRECTION_NE, DIRECTION_W, DIRECTION_E, DIRECTION_SW, DIRECTION_S, DIRECTION_SE};
enum LocationType {FLOOR, WALL, DOOR, EMPTY};
//


// Config and bootstrap methods
int screenSetup(void);
Room **mapSetup(void);

// Player methods
Player *playerSetup(void);
int playerMove(Player *user, enum Direction dir);
int playerDraw(Player *user);

// Room methods
Room *createRoom(int y, int x, int height, int width);
int drawRoom(Room *room);
const char *getDisplaySignForLocationType(enum LocationType locationType);
int connectLocations(Location loc1, Location loc2);

// Other methods
int handleInput(char, Player *user);
bool canGoToPosition(int y, int x);

#endif
