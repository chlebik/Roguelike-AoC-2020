#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <curses.h>

// Constants
const char *WALL_SIGN = "#";
const char *FLOOR_SIGN = ".";
const char *PLAYER_SIGN = "@";
//


// Structs
typedef struct Position {
    int x;
    int y;
} Position;

typedef struct Room {
    Position position;
    int height;
    int width;
} Room;

typedef struct Player {
    Position position;
    int health;
} Player;
//


// Enums
enum Direction {DIRECTION_NW, DIRECTION_N, DIRECTION_NE, DIRECTION_W, DIRECTION_E, DIRECTION_SW, DIRECTION_S, DIRECTION_SE};
//


// Config and bootstrap methods
int screenSetup(void);
Room **mapSetup(void);

// Player methods
Player *playerSetup(void);
int playerMove(Player *user, enum Direction dir);
int playerDraw(Player *user);

// Room methods
Room* createRoom(int y, int x, int height, int width);
int drawRoom(Room *room);

// Other methods
int handleInput(char, Player *user);
bool canGoToPosition(int y, int x);



int main()
{
    Player *user;
    char keyPressed;

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
    rooms[1] = createRoom(13, 30, 6, 9);
    drawRoom(rooms[1]);
    rooms[2] = createRoom(25, 13, 6, 12);
    drawRoom(rooms[2]);

    return rooms;
}

Room *createRoom(int y, int x, int height, int width)
{
    Room *newRoom = malloc(sizeof(Room));

    newRoom->position.y = y;
    newRoom->position.x = x;
    newRoom->height = height;
    newRoom->width = width;

    return newRoom;
}

int drawRoom(Room *room)
{
    int x, y;

    // Draw top and bottom
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
