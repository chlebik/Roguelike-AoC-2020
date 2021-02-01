#include <rogue.h>
#include <level.h>
#include <player.h>


void screenSetup(void)
{
    initscr();
    noecho();
    refresh();
}

void printGameHub(Level *level)
{
    mvprintw(40, 0, "    Level: %d", level->levelNumber);
    printw("    Gold: %d", level->user->gold);
    printw("    Hp: %d(%d)", level->user->health, level->user->maxHealth);
    printw("    Attack: %d", level->user->attack);
    printw("    Exp: %d", level->user->exp);
    printw("      ");
}