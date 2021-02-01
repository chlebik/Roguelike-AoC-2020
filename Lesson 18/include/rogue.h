#ifndef ROGUE_H
#define ROGUE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <curses.h>
#include <time.h>

#define ALLOWED_ROOM_LOCATIONS_NUMBER 4
#define NUMBER_OF_ROOMS 6
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
    int attack;
    int gold;
    int maxHealth;
    int exp;
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
    bool alive;
} Monster;

typedef struct Level {
    // Metadata
    int numberOfRooms;

    int levelNumber;
    int numberOfMonsters;

    // Elements of the level
    Room **rooms;
    Location **locations;
    Monster **monsters;
    Player *user;
} Level;
//


// Enums
enum Direction {DIRECTION_NW, DIRECTION_N, DIRECTION_NE, DIRECTION_W, DIRECTION_E, DIRECTION_SW, DIRECTION_S, DIRECTION_SE};
enum LocationType {FLOOR, WALL, DOOR, EMPTY};
//


// Config and bootstrap functions
int screenSetup(void);
Room **roomsSetup(int numberOfRooms);
int printGameHub(Level * level);

// Level functions
Level *createLevel(int levelNumber, int numberOfRooms, int numberOfMonsters);
void saveLevelLocations(Level *level);

// Player functions
Player *playerSetup(void);
int playerMove(Level *level, enum Direction dir);
int playerDraw(Player *user);
int placePlayerInTheLevel(Level *level);

// Room functions
Room *createRoom(int grid);
int drawRoom(Room *room);
char *getDisplaySignForLocationType(enum LocationType locationType);
int connectLocations(Location firstDoor, Location secondDoor);

// Monsters functions
void createMonsters(Level *level,  Room **rooms);
Monster *createMonster();
Monster *createMonsterObject(char *displaySign, int health, int attack, int speed, int defence, bool pathfinding);
void placeMonsterInTheLevel(Monster *monster, Room room);
void drawMonsters(Level *level);
Monster *getMonsterAt(Location *location, Monster **monsters);
bool isMonsterOnLocation(Location *location, Monster **monsters);
int killMonster(Monster *monster);

// Pathfinding
int pathfindingSeek(Monster *monster, Location *userLocation);
int pathfindingRandom(Monster *monster);
int moveMonsters(Level *level);

// Combat
int combat(Player *player, Monster *monster, bool playerFirst);

// Other functions
int handleInput(char keyPressed, Level *level);
bool canGoToPosition(int y, int x);

#endif
