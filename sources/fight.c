
#include "fight.h"

// character can shoot with o,k,l,m (up, left, down, right)
// a shoot ps is stopped by a wall, a monster or a rock
// a shoot ss is stopped by a wall or a rock

// a monster can attack character body to body or shoot
//  - dmg: one shield else one hp

void dmgMonster(Level *level, int h, int w)
{
    MonsterList *monsters = level->currentRoom->monsters;
    for (int i = 0; i < monsters->size; i += 1)
    {
        if ((monsters->list[i]->p.h == h) && (monsters->list[i]->p.w == w))
        {
            if (touched(monsters->list[i], level->player->dmg) == 0)
            {
                level->currentRoom->map[monsters->list[i]->p.h][monsters->list[i]->p.w] = ' ';
                removeMonsterByIndex(i, monsters);
            }
        }
    }
}

boolean isClear(Level *level, int h, int w)
{
    return !(
        isWall(level, h, w) || isRock(level, h, w) || isMonster(level, h, w));
}

boolean noObstacle(Level *level, int h, int w)
{
    return !(
        isWall(level, h, w) || isRock(level, h, w) || isGap(level, h, w) || isPerson(level, h, w));
}

void upSS(Level *level, int h, int w)
{
    int n = 1;
    while ((h - n) > 0)
    {
        // not wall, not rock
        if (isClear(level, h - n, w))
        {
            if (level->currentRoom->map[h - n][w] == ' ')
            {
                level->currentRoom->map[h - n][w] = '+';
                showCurrentRoom(level);
                clock_t start = clock();
                while (clock() < start + 30000)
                {
                }
            }
        }
        else
        {
            if (isMonster(level, h - n, w))
            {
                dmgMonster(level, h - n, w);
            }
        }
        n += 1;
    }

    for (int j = 1; j < n; j += 1)
    {
        if (level->currentRoom->map[h - j][w] == '+')
        {
            level->currentRoom->map[h - j][w] = ' ';
        }
        showCurrentRoom(level);
        clock_t start = clock();
        while (clock() < start + 20000)
        {
        }
    }
}

void upShoot(Level *level, int h, int w)
{
    int n = 1;
    while ((h - n) > 0)
    {
        // not wall, not rock and not monster
        if (isClear(level, h - n, w))
        {
            if (level->currentRoom->map[h - n][w] == ' ')
            {
                level->currentRoom->map[h - n][w] = '|';
                showCurrentRoom(level);
                clock_t start = clock();
                while (clock() < start + 30000)
                {
                }
            }
        }
        else
        {
            if (isMonster(level, h - n, w))
            {
                dmgMonster(level, h - n, w);
            }
            break;
        }
        n += 1;
    }

    for (int j = 1; j < n; j += 1)
    {
        if (level->currentRoom->map[h - j][w] == '|')
        {
            level->currentRoom->map[h - j][w] = ' ';
        }
        showCurrentRoom(level);
        clock_t start = clock();
        while (clock() < start + 20000)
        {
        }
    }
}

void leftSS(Level *level, int h, int w)
{
    int n = 1;
    while ((w - n) > 0)
    {
        // not wall, not rock and not monster
        if (isClear(level, h, w - n))
        {
            if (level->currentRoom->map[h][w - n] == ' ')
            {
                level->currentRoom->map[h][w - n] = '+';
                showCurrentRoom(level);
                clock_t start = clock();
                while (clock() < start + 30000)
                {
                }
            }
        }
        else
        {
            if (isMonster(level, h, w - n))
            {
                dmgMonster(level, h, w - n);
            }
        }
        n += 1;
    }

    for (int j = 1; j < n; j += 1)
    {
        if (level->currentRoom->map[h][w - j] == '+')
        {
            level->currentRoom->map[h][w - j] = ' ';
        }
        showCurrentRoom(level);
        clock_t start = clock();
        while (clock() < start + 20000)
        {
        }
    }
}

void leftShoot(Level *level, int h, int w)
{
    int n = 1;
    while ((w - n) > 0)
    {
        // non wall, no rock, no monster
        if (isClear(level, h, w - n))
        {
            if (level->currentRoom->map[h][w - n] == ' ')
            {
                level->currentRoom->map[h][w - n] = '-';
                showCurrentRoom(level);
                clock_t start = clock();
                while (clock() < start + 30000)
                {
                }
            }
        }
        else
        {
            if (isMonster(level, h, w - n))
            {
                dmgMonster(level, h, w - n);
            }
            break;
        }
        n += 1;
    }

    for (int j = 1; j < n; j += 1)
    {
        if (level->currentRoom->map[h][w - j] == '-')
        {
            level->currentRoom->map[h][w - j] = ' ';
        }
        showCurrentRoom(level);
        clock_t start = clock();
        while (clock() < start + 20000)
        {
        }
    }
}

void downSS(Level *level, int h, int w)
{
    int n = 1;
    while ((h + n) < level->rows - 1)
    {
        // not wall, not rock and not monster
        if (isClear(level, h + n, w))
        {
            if (level->currentRoom->map[h + n][w] == ' ')
            {
                level->currentRoom->map[h + n][w] = '+';
            }
            showCurrentRoom(level);
            clock_t start = clock();
            while (clock() < start + 30000)
            {
            }
        }
        else
        {
            if (isMonster(level, h + n, w))
            {
                dmgMonster(level, h + n, w);
            }
        }
        n += 1;
    }

    for (int j = 1; j < n; j += 1)
    {
        if (level->currentRoom->map[h + j][w] == '+')
        {
            level->currentRoom->map[h + j][w] = ' ';
        }
        showCurrentRoom(level);
        clock_t start = clock();
        while (clock() < start + 20000)
        {
        }
    }
}

void downShoot(Level *level, int h, int w)
{
    int n = 1;
    while ((h + n) < level->rows - 1)
    {
        if (isClear(level, h + n, w))
        {
            if (level->currentRoom->map[h + n][w] == ' ')
            {
                level->currentRoom->map[h + n][w] = '|';
                showCurrentRoom(level);
                clock_t start = clock();
                while (clock() < start + 30000)
                {
                }
            }
        }
        else
        {
            if (isMonster(level, h + n, w))
            {
                dmgMonster(level, h + n, w);
            }
            break;
        }
        n += 1;
    }

    for (int j = 1; j < n; j += 1)
    {
        if (level->currentRoom->map[h + j][w] == '|')
        {
            level->currentRoom->map[h + j][w] = ' ';
        }
        showCurrentRoom(level);
        clock_t start = clock();
        while (clock() < start + 20000)
        {
        }
    }
}

void rightSS(Level *level, int h, int w)
{
    int n = 1;
    while ((w + n) < level->columns - 1)
    {
        // not wall, not rock and not monster
        if (isClear(level, h, w + n))
        {
            if (level->currentRoom->map[h][w + n] == ' ')
            {
                level->currentRoom->map[h][w + n] = '+';
                showCurrentRoom(level);
                clock_t start = clock();
                while (clock() < start + 30000)
                {
                }
            }
        }
        else
        {
            if (isMonster(level, h, w + n))
            {
                dmgMonster(level, h, w + n);
            }
        }
        n += 1;
    }

    for (int j = 1; j < n; j += 1)
    {
        if (level->currentRoom->map[h][w + j] == '+')
        {
            level->currentRoom->map[h][w + j] = ' ';
        }
        showCurrentRoom(level);
        clock_t start = clock();
        while (clock() < start + 20000)
        {
        }
    }
}

void rightShoot(Level *level, int h, int w)
{
    int n = 1;
    while ((w + n) < level->columns - 1)
    {
        if (isClear(level, h, w + n))
        {
            if (level->currentRoom->map[h][w + n] == ' ')
            {
                level->currentRoom->map[h][w + n] = '-';
                showCurrentRoom(level);
                clock_t start = clock();
                while (clock() < start + 30000)
                {
                }
            }
        }
        else
        {
            if (isMonster(level, h, w + n))
            {
                dmgMonster(level, h, w + n);
            }
            break;
        }
        n += 1;
    }

    for (int j = 1; j < n; j += 1)
    {
        if (level->currentRoom->map[h][w + j] == '-')
        {
            level->currentRoom->map[h][w + j] = ' ';
        }
        showCurrentRoom(level);
        clock_t start = clock();
        while (clock() < start + 20000)
        {
        }
    }
}

void shoot(Level *level, char letter)
{
    int h = level->coord.p.h;
    int w = level->coord.p.w;
    if (isSpectral(level))
    {
        switch (letter)
        {
        case 'o':
            upSS(level, h, w);
            break;

        case 'k':
            leftSS(level, h, w);
            break;

        case 'l':
            downSS(level, h, w);
            break;

        case 'm':
            rightSS(level, h, w);
            break;
        }
    }
    else
    {
        switch (letter)
        {
        case 'o':
            upShoot(level, h, w);
            break;

        case 'k':
            leftShoot(level, h, w);
            break;

        case 'l':
            downShoot(level, h, w);
            break;

        case 'm':
            rightShoot(level, h, w);
            break;
        }
    }
}

/**
 * @brief Direction taken by monster to reach 'P'
 *
 * @param level
 * @param index
 * @return direction (North, East, South, West)
 */
direction directionToTakeMonster(Level *level, Monster *m)
{
    direction way;
    int dh = level->coord.p.h - m->p.h;
    int dw = level->coord.p.w - m->p.w;

    if (dh == 0)
    {
        if (dw > 0)
        {
            way = East;
        }
        else
        {
            way = West;
        }
    }
    else if (dw == 0)
    {
        if (dh < 0)
        {
            way = North;
        }
        else
        {
            way = South;
        }
    }
    else if (dh > 0)
    {
        way = South;
    }
    else
    {
        way = North;
    }
    return way;
}

boolean directionTakenMonster(Level *level, Monster *m, direction cardinal)
{
    boolean takeDirection = false;

    switch (cardinal)
    {
    case North:
        if (noObstacle(level, m->p.h - 1, m->p.w))
        {
            m->p.h -= 1;
            takeDirection = true;
        }
        break;

    case East:
        if (noObstacle(level, m->p.h, m->p.w + 1))
        {
            m->p.w += 1;
            takeDirection = true;
        }
        break;

    case South:
        if (noObstacle(level, m->p.h + 1, m->p.w))
        {
            m->p.h += 1;
            takeDirection = true;
        }
        break;
    case West:
        if (noObstacle(level, m->p.h, m->p.w - 1))
        {
            m->p.w -= 1;
            takeDirection = true;
        }
        break;
    }
    return takeDirection;
}

void movedMonster(Level *level, Monster *m)
{
    // current point
    if (level->currentRoom->map[m->p.h][m->p.w] == 'M')
    {
        level->currentRoom->map[m->p.h][m->p.w] = ' ';
    }
    if (isSpike(level, m->p.h, m->p.w))
    {
        // loose 0.5 hp if the point of the player is 'S'
        ouch(level->player, 0.5);
    }

    // monster moved to cardinal direction
    direction way = directionToTakeMonster(level, m);
    boolean takeDirection = directionTakenMonster(level, m, way);
    while (!takeDirection)
    {
        way = (way + 1) % 4;
        takeDirection = directionTakenMonster(level, m, way);
    }

    // mark 'M' if next point is empty
    if (isBlank(level, m->p.h, m->p.w))
    {
        level->currentRoom->map[m->p.h][m->p.w] = 'M';
    }
}

void restlessMonsters(Level *level)
{
    if (isType(level, level->coord.u, level->coord.v, "Room"))
    {
        MonsterList *monsters = level->currentRoom->monsters;
        if (monsters->size)
        {
            printf("=======monsters: %p, size: %d, list[1]: %p=========", monsters, monsters->size, monsters->list[1]);

            northDoor(level, level->coord.u, level->coord.v, 'W');
            eastDoor(level, level->coord.u, level->coord.v, 'W');
            westDoor(level, level->coord.u, level->coord.v, 'W');
            southDoor(level, level->coord.u, level->coord.v, 'W');
            for (int i = 0; i < monsters->size; i += 1)
            {
                movedMonster(level, monsters->list[i]);
                sideAttack(level, monsters->list[i]);
            }
        }
        else
        {
            northDoor(level, level->coord.u, level->coord.v, level->currentRoom->upDoor);
            eastDoor(level, level->coord.u, level->coord.v, level->currentRoom->rightDoor);
            westDoor(level, level->coord.u, level->coord.v, level->currentRoom->leftDoor);
            southDoor(level, level->coord.u, level->coord.v, level->currentRoom->downDoor);
        }
    }
}

void sideAttack(Level *level, Monster *m)
{
    if (isSideBySide(level, m))
    {
        dmgPlayer(level);
    }
}

/**
 * @brief return true if the monster is next to the character
 *
 * @param level
 * @param m
 * @return boolean
 */
boolean isSideBySide(Level *level, Monster *m)
{
    if (!strcmp(level->currentRoom->type, "Room"))
    {
        return (isPerson(level, m->p.h, m->p.w - 1) || isPerson(level, m->p.h, m->p.w + 1) || isPerson(level, m->p.h - 1, m->p.w) || isPerson(level, m->p.h + 1, m->p.w));
    }
    return false;
}

void dmgPlayer(Level *level)
{
    if (level->player->shield > 0)
    {
        level->player->shield -= 1;
    }
    else
    {
        ouch(level->player, 1);
    }
}

boolean canShoot(Level *level)
{
    return (level->player->ps || level->player->ss);
}

boolean isSpectral(Level *level)
{
    return level->player->ss;
}
