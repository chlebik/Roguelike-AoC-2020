#ifndef ROOM_H
#define ROOM_H

#include "level.h"
#include "monster.h"

typedef struct Room {
    struct Position position;
    int height;
    int width;
    struct Location locations[ALLOWED_ROOM_LOCATIONS_NUMBER];
} Room;

Room **roomsSetup(int numberOfRooms);
Room *createRoom(int grid);
char *getDisplaySignForLocationType(enum LocationType locationType);
char *resolveDisplaySignFromChar(char signOnScreen);
void drawRoom(Room *room);

bool canGoToLocation(struct Location location, struct Player player, struct Monster **monsters);


#endif
