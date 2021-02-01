#include <rogue.h>


int connectLocations(const Location firstDoor, const Location secondDoor)
{
    Location temp = firstDoor;
    Location previous = firstDoor;

    int count = 0;

    while (1) {

        previous.displaySign = unctrl(mvinch(temp.position.y, temp.position.x));
        previous.position.x = temp.position.x;
        previous.position.y = temp.position.y;

        // step left
        if ((abs((temp.position.x - 1) - secondDoor.position.x) < abs(temp.position.x - secondDoor.position.x)) &&
            ((mvinch(temp.position.y, temp.position.x - 1) == *EMPTY_SIGN) || (mvinch(temp.position.y, temp.position.x - 1) == *FLOOR_SIGN))) {
            temp.position.x = temp.position.x - 1;
            // step right
        } else if ((abs((temp.position.x + 1) - secondDoor.position.x) < abs(temp.position.x - secondDoor.position.x))  &&
                   ((mvinch(temp.position.y, temp.position.x + 1) == *EMPTY_SIGN) || (mvinch(temp.position.y, temp.position.x + 1) == *FLOOR_SIGN))) {
            temp.position.x = temp.position.x + 1;
            // step down
        } else if ((abs((temp.position.y + 1) - secondDoor.position.y) < abs(temp.position.y - secondDoor.position.y)) &&
                   ((mvinch(temp.position.y + 1, temp.position.x) == *EMPTY_SIGN) || (mvinch(temp.position.y + 1, temp.position.x) == *FLOOR_SIGN))) {
            temp.position.y = temp.position.y + 1;
            // step up
        } else if ((abs((temp.position.y - 1) - secondDoor.position.y) < abs(temp.position.y - secondDoor.position.y)) &&
                   ((mvinch(temp.position.y - 1, temp.position.x) == *EMPTY_SIGN) || (mvinch(temp.position.y - 1, temp.position.x) == *FLOOR_SIGN))) {
            temp.position.y = temp.position.y - 1;
        } else {

            mvprintw(previous.position.y, previous.position.x, previous.displaySign);

            if (count == 0) {
                temp = previous;
                count++;
                continue;
            } else {
                return 0;
            }
        }

        mvprintw(temp.position.y, temp.position.x, FLOOR_SIGN);
    }
}


Room **roomsSetup(int numberOfRooms)
{
    int howManyConnectionsWeWant = 2;
    Room **rooms = malloc(sizeof(Room) * numberOfRooms);


    rooms[0] = createRoom(13, 13, 6, 9);
    drawRoom(rooms[0]);
    rooms[1] = createRoom(13, 30, 6, 10);
    drawRoom(rooms[1]);
    rooms[2] = createRoom(25, 13, 6, 12);
    drawRoom(rooms[2]);


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

        connectLocations(rooms[idOfFirstRoom]->locations[idOfDoorInFirstRoom], rooms[idOfSecondRoom]->locations[idOfDoorInSecondRoom]);
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


Room *createRoom(int y, int x, int height, int width)
{
    int doorsToCreate = (rand() % 2) + 1;  // We only set 2 doors per room - but it can be customized with this variable

    Room *newRoom = malloc(sizeof(Room));
    newRoom->position.y = y;
    newRoom->position.x = x;
    newRoom->height = height;
    newRoom->width = width;

    for(int i = 0; i < doorsToCreate; i++) {

        /*
          We randomize the location of the door, however we do not care
          if there are two doors on one wall (or even on the same location!).
          That makes it more randomized. We only omit corners.
        */
        switch (rand() % 4) {
            case 0: // North wall
                newRoom->locations[i].position.x = (x + 1)  + ((rand() % (width - 2)));
                newRoom->locations[i].position.y = y;
                break;
            case 1: // East wall
                newRoom->locations[i].position.x = x + width - 1;
                newRoom->locations[i].position.y = (y + 1) + ((rand() % (height - 2)));
                break;
            case 2: // South wall
                newRoom->locations[i].position.x = (x + 1)  + ((rand() % (width - 2)));
                newRoom->locations[i].position.y = y - 1 + height;
                break;

            case 3: // West wall
                newRoom->locations[i].position.x = x;
                newRoom->locations[i].position.y = (y + 1) + ((rand() % (height - 2)));
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
