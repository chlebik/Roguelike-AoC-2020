#include <rogue.h>
#include <utils.h>


Room **roomsSetup(int numberOfRooms)
{
    int howManyConnectionsWeWant = 4;
    Room **rooms = malloc(sizeof(Room) * numberOfRooms);

    for(int i = 0; i < numberOfRooms; i++) {
        rooms[i] = createRoom(i);
        drawRoom(rooms[i]);
    }

    for(int i = 0; i < howManyConnectionsWeWant; i++) {
        int idOfFirstRoom = rand() % numberOfRooms;
        int idOfSecondRoom;
        int idOfDoorInFirstRoom;
        int idOfDoorInSecondRoom;

        // Find out second room to connect to (it must be different than the already chosen one)
        while (1) {
            idOfSecondRoom = rand() % numberOfRooms;
            if(idOfSecondRoom != idOfFirstRoom) {
                break;
            }
        }

        // Having two rooms chosen we iterate over their locations to find unconnected doors
        // We do not care if doors used for connections are used more than once
        int idsOfRoomsToUse[2] = {idOfFirstRoom, idOfSecondRoom};
        for(int j = 0; j < 2; j++) {
            while (1) {

                int idOfRoomLocation = rand() % ALLOWED_ROOM_LOCATIONS_NUMBER;
                int idOfRoomToUse = idsOfRoomsToUse[j];
                Location randomDoorInRoom = rooms[idOfRoomToUse]->locations[idOfRoomLocation];

                if(randomDoorInRoom.displaySign == DOOR_SIGN) {    // index actually contains a location

                    if(j == 0) {
                        idOfDoorInFirstRoom = idOfRoomLocation;
                    } else {
                        idOfDoorInSecondRoom = idOfRoomLocation;
                    }

                    break;
                }
            }
        }

        pathFind(rooms[idOfFirstRoom]->locations[idOfDoorInFirstRoom].position, rooms[idOfSecondRoom]->locations[idOfDoorInSecondRoom].position);
    }

    return rooms;
}

bool canGoToPosition(int y, int x)
{
    const int ALLOWED_LOCATIONS_SIZE = 2;   // Hard-coded to simplify iteration loop
    char allowedLocations[] = {*FLOOR_SIGN, *DOOR_SIGN};
    char locationToCheck = mvinch(y, x);

    for(int i = 0; i < ALLOWED_LOCATIONS_SIZE; i++) {
        if(locationToCheck == allowedLocations[i]) {
            return TRUE;
        }
    }

    return FALSE;
}


Room *createRoom(int grid)
{
    int doorsToCreate = (rand() % 2) + 1;  // We only set 2 doors per room - but it can be customized with this variable
    Room *newRoom = malloc(sizeof(Room));

    switch (grid) {
        case 0:
            newRoom->position.x = 0;
            newRoom->position.y = 0;
            break;
        case 1:
            newRoom->position.x = 33;
            newRoom->position.y = 0;
            break;
        case 2:
            newRoom->position.x = 66;
            newRoom->position.y = 0;
            break;
        case 3:
            newRoom->position.x = 0;
            newRoom->position.y = 14;
            break;

        case 4:
            newRoom->position.x = 33;
            newRoom->position.y = 14;
            break;
        case 5:
            newRoom->position.x = 66;
            newRoom->position.y = 14;
            break;
    }

    newRoom->height = rand() % 6 + 4;
    newRoom->width = rand() % 14 + 4;

    /* offset */
    newRoom->position.x += rand() % (29 - newRoom->width + 1);
    newRoom->position.y += rand() % (9 - newRoom->height + 1);

    for(int i = 0; i < doorsToCreate; i++) {

        /*
          We randomize the location of the door, however we do not care
          if there are two doors on one wall (or even on the same location!).
          That makes it more randomized. We only omit corners.
        */
        switch (rand() % 4) {
            case 0: // North wall
                newRoom->locations[i].position.x = (newRoom->position.x + 1)  + ((rand() % (newRoom->width - 2)));
                newRoom->locations[i].position.y = newRoom->position.y;
                break;
            case 1: // East wall
                newRoom->locations[i].position.x = newRoom->position.x + newRoom->width - 1;
                newRoom->locations[i].position.y = (newRoom->position.y + 1) + ((rand() % (newRoom->height - 2)));
                break;
            case 2: // South wall
                newRoom->locations[i].position.x = (newRoom->position.x + 1)  + ((rand() % (newRoom->width - 2)));
                newRoom->locations[i].position.y = newRoom->position.y - 1 + newRoom->height;
                break;

            case 3: // West wall
                newRoom->locations[i].position.x = newRoom->position.x;
                newRoom->locations[i].position.y = (newRoom->position.y + 1) + ((rand() % (newRoom->height - 2)));
                break;
        }

        newRoom->locations[i].displaySign = getDisplaySignForLocationType(DOOR);
    }

    return newRoom;
}

char *getDisplaySignForLocationType(enum LocationType locationType) {

    switch (locationType) {
        case DOOR:
            return DOOR_SIGN;
        case FLOOR:
            return FLOOR_SIGN;
        case WALL:
            return WALL_SIGN;
        case EMPTY:
            return EMPTY_SIGN;
        default:
            return WALL_SIGN; // To avoid possible errors
    }
}

char *resolveDisplaySignFromChar(char signOnScreen)
{
    if(signOnScreen == *FLOOR_SIGN) {
        return getDisplaySignForLocationType(FLOOR);
    }

    if(signOnScreen == *WALL_SIGN) {
        return getDisplaySignForLocationType(WALL);
    }

    if(signOnScreen == *DOOR_SIGN) {
        return getDisplaySignForLocationType(DOOR);
    }

    if(signOnScreen == *EMPTY_SIGN) {
        return getDisplaySignForLocationType(EMPTY);
    }

    // Default value - to at least have some fallback
    return getDisplaySignForLocationType(EMPTY);
}

int drawRoom(Room *room)
{
    int x, y;

    // Draw top and bottom wall
    for(x = room->position.x; x < room->position.x + room->width; x++) {
        mvprintw(room->position.y, x, WALL_SIGN);
        mvprintw(room->position.y + room->height - 1, x, WALL_SIGN);
    }

    // Draw floors and side walls
    for(y = room->position.y + 1; y < room->position.y + room->height - 1; y++) {
        // Draw side walls
        mvprintw(y, room->position.x, WALL_SIGN);
        mvprintw(y, room->position.x + room->width - 1, WALL_SIGN);

        // Draw floor inside specific row
        for(x = room->position.x + 1; x < room->position.x + room->width - 1; x++) {
            mvprintw(y, x, FLOOR_SIGN);
        }
    }

    // Drawing of locations - for the time being there are only doors
    for(int i = 0; i < (sizeof room->locations / sizeof room->locations[0]); i++) {
        if(room->locations[i].displaySign) {
            mvprintw(room->locations[i].position.y, room->locations[i].position.x, room->locations[i].displaySign);
        }
    }

    return 0;
}
