/*
**  Filename : move.c
**
**  Made by : HT
**
**  Description : attempt to start the bob's game
*/

#include "room.h"
#include "level.h"
#include <unistd.h>
#include <stdlib.h>

#include <termios.h>
#include <unistd.h>
#include <fcntl.h>

// tput cols => 204
// tput lines => 52
void showCurrentRoom(Level *level)
{
    for (int i = 0; i < 15; i += 1)
    {
        printf("\n");
    }

    showRoom(level->floor[level->coord.u][level->coord.v]);
    printf("getU: %d, getV: %d\n", level->coord.u, level->coord.v);
}
int kbhit(void)
{
    struct termios oldt, newt;
    int ch;
    int oldf;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

    ch = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);

    if (ch != EOF)
    {
        ungetc(ch, stdin);
        return 1;
    }

    return 0;
}

void game(Level* level)
{
    char c;
    while (1)
    {

        system("clear");
        system("echo '\e[032m'");
        showCurrentRoom(level);
        while (!kbhit())
        {
        }
        c = getchar();

        printf("char:%c\n", c);
        fflush(stdin);
        sleep(1);
    }
}

