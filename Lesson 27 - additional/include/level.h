#ifndef LEVEL_H
#define LEVEL_H


typedef struct Position {
    int x;
    int y;
} Position;

typedef struct Location {
    struct Position position;
    char *displaySign;
} Location;

typedef struct Level {
    // Metadata
    int numberOfRooms;

    int levelNumber;
    int numberOfMonsters;

    // Elements of the level
    struct Room **rooms;
    struct Location **locations;
    struct Monster **monsters;
    struct Player *player;
} Level;

Level *createLevel(int levelNumber, int numberOfRooms, int numberOfMonsters);
void saveLevelLocations(Level *level);
void drawLevel(Level *level);

#endif
