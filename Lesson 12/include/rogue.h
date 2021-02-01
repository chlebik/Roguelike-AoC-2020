#ifndef ROGUE_H
#define ROGUE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <curses.h>
#include <time.h>

#define ALLOWED_ROOM_LOCATIONS_NUMBER 4
#define NUMBER_OF_ROOMS 3
#define NUMBER_OF_MONSTERS 6
#define DEFAULT_LEVEL_NUMBER 1

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
    char *displaySign;
} Location;

typedef struct Room {
    Position position;
    int height;
    int width;
    Location locations[ALLOWED_ROOM_LOCATIONS_NUMBER];
} Room;

typedef struct Player {
    Location *currentLocation;
    Location *previousLocation;
    int health;
} Player;

typedef struct Monster {
    char *displaySign;
    Location *currentLocation;
    Location *previousLocation;
    int health;
    int attack;
    int speed;
    int defence;
    bool pathfinding;
} Monster;

typedef struct Level {
    // Metadata
    int numberOfRooms;
    int levelNumber;
    int numberOfMonsters;

    // Elements of the level
    Location **locations;
    Monster **monsters;
} Level;
//


// Enums
enum Direction {DIRECTION_NW, DIRECTION_N, DIRECTION_NE, DIRECTION_W, DIRECTION_E, DIRECTION_SW, DIRECTION_S, DIRECTION_SE};
enum LocationType {FLOOR, WALL, DOOR, EMPTY};
//


// Config and bootstrap functions
int screenSetup(void);
Room **roomsSetup(int numberOfRooms);

// Level functions
Level *createLevel(int levelNumber, int numberOfRooms, int numberOfMonsters);
void saveLevelLocations(Level *level);

// Player functions
Player *playerSetup(void);
int playerMove(Player *user, enum Direction dir);
int playerDraw(Player *user);

// Room functions
Room *createRoom(int y, int x, int height, int width);
int drawRoom(Room *room);
char *getDisplaySignForLocationType(enum LocationType locationType);
int connectLocations(Location firstDoor, Location secondDoor);

// Monsters functions
void createMonsters(Level *level,  Room **rooms);
Monster *createMonster();
Monster *createMonsterObject(char *displaySign, int health, int attack, int speed, int defence, bool pathfinding);
void placeMonsterInTheLevel(Monster *monster, Room room);
void drawMonsters(Level *level);

// Other functions
int handleInput(char, Player *user);
bool canGoToPosition(int y, int x);

#endif
