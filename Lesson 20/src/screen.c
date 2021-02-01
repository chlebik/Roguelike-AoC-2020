#include <rogue.h>


int screenSetup(void)
{
    initscr();
    noecho();
    refresh();

    return 0;
}

int printGameHub(Level * level)
{
    mvprintw(40, 0, "    Level: %d", level->levelNumber);
    printw("    Gold: %d", level->user->gold);
    printw("    Hp: %d(%d)", level->user->health, level->user->maxHealth);
    printw("    Attack: %d", level->user->attack);
    printw("    Exp: %d", level->user->exp);
    printw("      ");

    return 0;
}