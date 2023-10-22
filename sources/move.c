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
// tput cols => 204
// tput lines => 52
void showCurrentRoom(Level *level)
{
    for (int i = 0; i < 15; i += 1)
    {
        printf("\n");
    }

    showRoom(level->floor[level->coord.u][level->coord.v]);
    printf("h: %d, w: %d\n", level->coord.p.h, level->coord.p.w);
}

void updateCurrentRoom(Level *level, int h, int w)
{
    if (h > level->rows - 1 || h < 0 || w < 0 || w > level->columns - 1)
    {
        return;
    }
    if (level->currentRoom->map[level->coord.p.h][level->coord.p.w] == 'P')
    {
        level->currentRoom->map[level->coord.p.h][level->coord.p.w] = ' ';
    }

    // next position of the character 'P'
    level->coord.p.h = h;
    level->coord.p.w = w;
    if (level->currentRoom->map[level->coord.p.h][level->coord.p.w] == ' ')
    {
        level->currentRoom->map[level->coord.p.h][level->coord.p.w] = level->character;
    }
    level->floor[level->coord.u][level->coord.v] = *level->currentRoom;
}

// no wall
int isSafe(Level *level, int h, int w)
{
    if (isWall(level, h, w))
    {
        return 0;
    }
    return 1;
}


void changeRoom(Level *level)
{
    if (level->coord.p.h == level->rows / 2)
    {
        // EAST DOOR
        if (level->coord.p.w == level->columns - 1)
        {
            level->coord.v = level->coord.v + 1;
            level->coord.p.w = 1;
        }

        // WEST DOOR
        if (level->coord.p.w == 0)
        {
            level->coord.v = level->coord.v - 1;
            level->coord.p.w = level->columns - 2;
        }
    }
    if (level->coord.p.w == level->columns / 2)
    {
        // SOUTH DOOR
        if (level->coord.p.h == level->rows - 1)
        {
            level->coord.u = level->coord.u + 1;
            level->coord.p.h = 1;
        }

        // NORTH DOOR
        if (level->coord.p.h == 0)
        {
            level->coord.u = level->coord.u - 1;
            level->coord.p.h = level->rows - 2;
        }
    }
    // update currentRoom
    *level->currentRoom = level->floor[level->coord.u][level->coord.v];

    // 'P' passe au travers des obstacles sauf 'W'
    if (level->currentRoom->map[level->coord.p.h][level->coord.p.w] == ' ')
    {
        level->currentRoom->map[level->coord.p.h][level->coord.p.w] = level->character;
    }
}

void movePerson(Level *level, char key)
{
    switch (key)
    {
    case 'z':
        if (isSafe(level, level->coord.p.h - 1, level->coord.p.w))
        {
            updateCurrentRoom(level, level->coord.p.h - 1, level->coord.p.w);
        }
        break;

    case 'd':
        if (isSafe(level, level->coord.p.h, level->coord.p.w + 1))
        {
            updateCurrentRoom(level, level->coord.p.h, level->coord.p.w + 1);
        }
        break;

    case 's':
        if (isSafe(level, level->coord.p.h + 1, level->coord.p.w))
        {
            updateCurrentRoom(level, level->coord.p.h + 1, level->coord.p.w);
        }
        break;

    case 'q':
        if (isSafe(level, level->coord.p.h, level->coord.p.w - 1))
        {
            updateCurrentRoom(level, level->coord.p.h, level->coord.p.w - 1);
        }
        break;

    default:
        break;
    }
    changeRoom(level);
}

void game(Level *level)
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
        movePerson(level, c);
        fflush(stdin);
        // sleep(3);
    }
}

int isItem(Level* level, int h, int w){
    return level->currentRoom->map[h][w] == 'I';
}
int isDoor(Level* level, int h, int w){
    return level->currentRoom->map[h][w] == 'D';
}
int isBoss(Level* level, int h, int w){
    return level->currentRoom->map[h][w] == 'B';
}
int isHealth(Level* level, int h, int w){
    return level->currentRoom->map[h][w] == 'H';
}
/**
 * @brief Pic franchissable par le personnage et les monstres mais en prenant des dégâts
 */
int isSpike(Level* level, int h, int w){
    return level->currentRoom->map[h][w] == 'S';
}
/**
 * @brief Un trou infranchissable par le personnage et les monstres
 */
int isGap(Level* level, int h, int w){
    return level->currentRoom->map[h][w] == 'G';
}

/**
 * @brief Un rocher infranchissable par le personnage et les monstres
 */
int isRock(Level* level, int h, int w){
    return level->currentRoom->map[h][w] == 'R';
}

int isWall(Level* level, int h, int w){
    return level->currentRoom->map[h][w] == 'W';
}