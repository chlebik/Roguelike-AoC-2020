#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <curses.h>
#include <time.h>

// Constants
const char *WALL_SIGN = "#";
const char *FLOOR_SIGN = ".";
const char *PLAYER_SIGN = "@";
const char *DOOR_SIGN = "+";
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
    Location locations[4];
} Room;

typedef struct Player {
    Position position;
    int health;
} Player;
//


// Enums
enum Direction {DIRECTION_NW, DIRECTION_N, DIRECTION_NE, DIRECTION_W, DIRECTION_E, DIRECTION_SW, DIRECTION_S, DIRECTION_SE};
enum LocationType {FLOOR, WALL, DOOR};
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
    Room **rooms = malloc(sizeof(Room)*3);

    rooms[0] = createRoom(13, 13, 6, 9);
    drawRoom(rooms[0]);
    rooms[1] = createRoom(13, 30, 6, 10);
    drawRoom(rooms[1]);
    rooms[2] = createRoom(25, 13, 6, 12);
    drawRoom(rooms[2]);

    return rooms;
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
    const int ALLOWED_LOCATIONS_SIZE = 1;   // Hard-coded to simplify iteration loop
    char allowedLocations[] = {*FLOOR_SIGN};
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
