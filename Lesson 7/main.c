#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <curses.h>
#include <time.h>

#define ALLOWED_ROOM_LOCATIONS_NUMBER 4

// Constants
const char *WALL_SIGN = "#";
const char *FLOOR_SIGN = ".";
const char *PLAYER_SIGN = "@";
const char *DOOR_SIGN = "+";
const char *EMPTY_SIGN = " ";
//


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
int connectLocations(const Location loc1, const Location loc2);

// Other methods
int handleInput(char, Player *user);
bool canGoToPosition(int y, int x);



int main()
{
    Player *user;
    char keyPressed;
    srand(time(NULL));

    screenSetup();
    mapSetup();
    user = playerSetup();

    /* Main game loop */
    while((keyPressed = getch()) != 'q') {
        handleInput(keyPressed, user);
    }

	endwin();

	return 0;
}


Player *playerSetup(void)
{
    Player *newPlayer = malloc(sizeof(Player));
    newPlayer->position.x = 14;
    newPlayer->position.y = 14;
    newPlayer->health = 20;

    playerDraw(newPlayer);

    return newPlayer;
}

int screenSetup(void)
{
    initscr();
    printw("Roguelike game!");
    noecho();
    refresh();

    return 0;
}

Room **mapSetup(void)
{
    int numberOfRooms = 3;
    int totalNumberOfDoors = 0;
    int howManyConnectionsWeWant = 2;
    Location locationsToConnect[howManyConnectionsWeWant][2];    // Every connection is a pair of Positions
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

                if(randomDoorInRoom.displaySign == DOOR_SIGN    // index actually contains a location
                    ) {

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

int connectLocations(const Location loc1, const Location loc2)
{
    Position temp;
    Position doorTwo = loc2.position;

    temp.x = loc1.position.x;
    temp.y = loc1.position.y;

    while (1)
    {

        // step left
        if ((abs((temp.x - 1) - doorTwo.x) < abs(temp.x - doorTwo.x)) && (mvinch(temp.y, temp.x - 1) == ' ')) {
            temp.x = temp.x - 1;

        // step right
        } else if ((abs((temp.x + 1) - doorTwo.x) < abs(temp.x - doorTwo.x)) && (mvinch(temp.y, temp.x + 1) == ' ')) {
            temp.x = temp.x + 1;

        // step down
        } else if ((abs((temp.y + 1) - doorTwo.y) < abs(temp.y - doorTwo.y)) && (mvinch(temp.y + 1, temp.x) == ' ')) {
            temp.y = temp.y + 1;

        // step up
        } else if ((abs((temp.y - 1) - doorTwo.y) < abs(temp.y - doorTwo.y)) && (mvinch(temp.y - 1, temp.x) == ' ')) {
            temp.y = temp.y - 1;
        } else {
            return 0;
        }

        mvprintw(temp.y, temp.x, FLOOR_SIGN);

        getch();

    }

    return 0;
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

const char *getDisplaySignForLocationType(enum LocationType locationType) {

    switch (locationType) {
        case DOOR:
            return DOOR_SIGN;
            break;
        case FLOOR:
            return FLOOR_SIGN;
            break;
        case WALL:
            return WALL_SIGN;
            break;
        case EMPTY:
            return EMPTY_SIGN;
            break;
    }
    return WALL_SIGN;  // To avoid possible errors
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


int handleInput(char keyPressed, Player *user)
{
    switch (keyPressed) {
        // move up
        case 'w':
        case 'W':
            playerMove(user, DIRECTION_N);
            break;

        // move left
        case 'a':
        case 'A':
            playerMove(user, DIRECTION_W);
            break;

        // move right
        case 'd':
        case 'D':
            playerMove(user, DIRECTION_E);
            break;

        // move down
        case 's':
        case 'S':
            playerMove(user, DIRECTION_S);
            break;

        default:
            break;
    }

    return 0;
}


int playerMove(Player *user, enum Direction direction)
{
     int possibleX = user->position.x;
     int possibleY = user->position.y;

     switch (direction) {
        // move up
        case DIRECTION_N:
            possibleY -= 1;
            break;

        // move left
        case DIRECTION_W:
            possibleX -= 1;
            break;

        // move right
        case DIRECTION_E:
            possibleX += 1;
            break;

        // move down
        case DIRECTION_S:
            possibleY += 1;
            break;

        default:
            break; // We stay in place (usually 'turn' will pass then)
     }

    // Cleanup of current position
    mvprintw(user->position.y, user->position.x, FLOOR_SIGN);

    if(canGoToPosition(possibleY, possibleX)) {
        user->position.y = possibleY;
        user->position.x = possibleX;
    }

    // We redraw the player no matter if the position changed or not
    playerDraw(user);

    return 0;
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

int playerDraw(Player *user)
{
    mvprintw(user->position.y, user->position.x, PLAYER_SIGN);
    move(user->position.y, user->position.x);

    return 0;
}
