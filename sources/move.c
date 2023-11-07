/*
**  Filename : move.c
**
**  Made by : HT
**
**  Description :
*/

#include "move.h"
#include "fight.h"

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

int isItem(Level *level, int h, int w)
{
    return level->currentRoom->map[h][w] == 'I';
}
int isDoor(Level *level, int h, int w)
{
    return level->currentRoom->map[h][w] == 'D';
}
int isBoss(Level *level, int h, int w)
{
    return level->currentRoom->map[h][w] == 'B';
}
int isHealth(Level *level, int h, int w)
{
    return level->currentRoom->map[h][w] == 'H';
}
/**
 * @brief Pic franchissable par le personnage et les monstres mais en prenant des dégâts
 */
int isSpike(Level *level, int h, int w)
{
    return level->currentRoom->map[h][w] == 'S';
}
/**
 * @brief Un trou infranchissable par le personnage et les monstres
 */
int isGap(Level *level, int h, int w)
{
    return level->currentRoom->map[h][w] == 'G';
}

/**
 * @brief Un rocher infranchissable par le personnage et les monstres
 */
int isRock(Level *level, int h, int w)
{
    return level->currentRoom->map[h][w] == 'R';
}

int isWall(Level *level, int h, int w)
{
    return level->currentRoom->map[h][w] == 'W';
}

int isBlank(Level *level, int h, int w)
{
    return level->currentRoom->map[h][w] == ' ';
}

boolean isPerson(Level *level, int h, int w)
{
    return level->currentRoom->map[h][w] == 'P';
}

boolean isMonster(Level *level, int h, int w)
{
    return level->currentRoom->map[h][w] == 'M';
}

/**
 * @brief if the character 'P' change room:
 *          - update coordinates of the current room
 *          - update coordinates of the character in this new room
 *
 * @param level
 */
void reachCardinalPoint(Level *level)
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
}

// tput cols => 204
// tput lines => 52
void showCurrentRoom(Level *level)
{
    // clear screen
    system("clear");

    // color of the sceen
    system("echo '\e[032m'");

    for (int i = 0; i < 15; i += 1)
    {
        printf("\n");
    }

    // showRoom(level->floor[level->coord.u][level->coord.v]);
    showRoom(*level->currentRoom);
    printf("h: %d, w: %d\n", level->coord.p.h, level->coord.p.w);
}

void goToNextPoint(Level *level, int h, int w)
{
    if (h > level->rows - 1 || h < 0 || w < 0 || w > level->columns - 1)
    {
        return;
    }

    // current point
    if (level->currentRoom->map[level->coord.p.h][level->coord.p.w] == 'P')
    {
        level->currentRoom->map[level->coord.p.h][level->coord.p.w] = ' ';
    }
    if (isSpike(level, level->coord.p.h, level->coord.p.w))
    {
        // loose 0.5 hp if the point of the player is 'S'
        ouch(level->player, 0.5);
    }

    // next position of the character 'P'
    level->coord.p.h = h;
    level->coord.p.w = w;
}

// no wall, no gap, no rock, no character, no monster
int isSafe(Level *level, int h, int w)
{
    if (isWall(level, h, w) || isGap(level, h, w) || isRock(level, h, w) || isPerson(level, h, w) || isMonster(level, h, w))
    {
        return 0;
    }
    return 1;
}

void movePerson(Level *level, char key)
{
    switch (key)
    {
    case 'z':
        if (isSafe(level, level->coord.p.h - 1, level->coord.p.w))
        {
            goToNextPoint(level, level->coord.p.h - 1, level->coord.p.w);
        }
        break;

    case 'd':
        if (isSafe(level, level->coord.p.h, level->coord.p.w + 1))
        {
            goToNextPoint(level, level->coord.p.h, level->coord.p.w + 1);
        }
        break;

    case 's':
        if (isSafe(level, level->coord.p.h + 1, level->coord.p.w))
        {
            goToNextPoint(level, level->coord.p.h + 1, level->coord.p.w);
        }
        break;

    case 'q':
        if (isSafe(level, level->coord.p.h, level->coord.p.w - 1))
        {
            goToNextPoint(level, level->coord.p.h, level->coord.p.w - 1);
        }
        break;

    default:
        break;
    }

    // update floor with the value of currentRoom
    level->floor[level->coord.u][level->coord.v] = *level->currentRoom;

    // when changing room update all coordinates
    reachCardinalPoint(level);

    // upgrade if the next point of the player is 'I'
    if (isItem(level, level->coord.p.h, level->coord.p.w))
    {
        upgradePlayer(level->player, randomItem(level->pathItemfile));
    }

    // gain one life or one shield if the next point of the player is 'H'
    if (isHealth(level, level->coord.p.h, level->coord.p.w))
    {
        upgradePlayer(level->player, lifeOrShield());
    }

    // mark 'P' if next point is empty or item or health
    if (isBlank(level, level->coord.p.h, level->coord.p.w) || isItem(level, level->coord.p.h, level->coord.p.w) || isHealth(level, level->coord.p.h, level->coord.p.w))
    {
        if (level->player->state == inPain)
        {
            level->currentRoom->map[level->coord.p.h][level->coord.p.w] = 'b';
            showCurrentRoom(level);
            clock_t start = clock();
            while (clock() < start + 400000)
            {
            }
            level->player->state = inShape;
        }

        level->currentRoom->map[level->coord.p.h][level->coord.p.w] = level->character;
        showCurrentRoom(level);
    }

    // monsters moved in the direction of the character 'P'
    restlessMonsters(level);
}

void game(Level *level)
{
    char c;
    while (1)
    {
        showCurrentRoom(level);
        statsPlayer(level->player);

        while (!kbhit())
        {
        }
        c = getchar();

        // player can shoot with o
        if (canShoot(level))
        {
            shoot(level, c);
        }
        movePerson(level, c);

        fflush(stdin);
        //  sleep(3);
    }
}