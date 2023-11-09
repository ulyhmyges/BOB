
#include "fight.h"

// character can shoot with o,k,l,m (up, left, down, right)
// a shoot ps is stopped by a wall, a monster or a rock
// a shoot ss is stopped by a wall or a rock

// a monster can attack character body to body or by shooting

/**
 * @brief damage player of one shield or one hp
 *
 * @param level
 * @param h
 * @param w
 */
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

                // 5% of chance to leave an item 'H'
                if (chance())
                {
                    level->currentRoom->map[monsters->list[i]->p.h][monsters->list[i]->p.w] = 'H';
                }
                
                // leave an item 'I' after dead
                if (isType(level, level->currentRoom->spot.u, level->currentRoom->spot.v, "Boss"))
                {
                    level->currentRoom->map[level->rows/2][level->columns/2] = 'I';
                    showBonusRoom(level);
                    level->currentRoom->map[level->rows/4][level->columns/2+level->columns/4] = 'E';
                }
                removeMonsterByIndex(i, monsters);
            }
        }
    }
}

boolean isClear(Level *level, int h, int w)
{
    return !(
        isWall(level, h, w) || isRock(level, h, w) || isMonster(level, h, w) || isBoss(level, h, w));
}

boolean noObstacle(Level *level, int h, int w)
{
    return !(
        isWall(level, h, w) || isRock(level, h, w) || isGap(level, h, w) || isPerson(level, h, w) || isHealth(level, h, w) || isLock(level, h, w));
}

void upSS(Level *level, int h, int w)
{
    int n = 1;
    while ((h - n) > 0)
    {
        // not wall, not rock, no monster
        if (isClear(level, h - n, w))
        {
            if (level->currentRoom->map[h - n][w] == ' ')
            {
                level->currentRoom->map[h - n][w] = '+';
            }
            showCurrentRoom(level);
            clock_t start = clock();
            while (clock() < start + 20000)
            {
            }
            if (isPerson(level, h - n, w))
            {
                dmgPlayer(level);
            }
        }
        else
        {
            if (isMonster(level, h - n, w) || isBoss(level, h - n, w))
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
                while (clock() < start + 20000)
                {
                }
            }
            if (isPerson(level, h - n, w))
            {
                dmgPlayer(level);
                break;
            }
        }
        else
        {
            if (isMonster(level, h - n, w) || isBoss(level, h - n, w))
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
        // not wall, not rock, not monster and not boss
        if (isClear(level, h, w - n))
        {
            if (level->currentRoom->map[h][w - n] == ' ')
            {
                level->currentRoom->map[h][w - n] = '+';
            }
            showCurrentRoom(level);
            clock_t start = clock();
            while (clock() < start + 20000)
            {
            }
            if (isPerson(level, h, w - n))
            {
                dmgPlayer(level);
            }
        }
        else
        {
            if (isMonster(level, h, w - n) || isBoss(level, h, w - n))
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
                while (clock() < start + 20000)
                {
                }
            }
            if (isPerson(level, h, w - n))
            {
                dmgPlayer(level);
                break;
            }
        }
        else
        {
            if (isMonster(level, h, w - n) || isBoss(level, h, w - n))
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
            while (clock() < start + 20000)
            {
            }
            if (isPerson(level, h + n, w))
            {
                dmgPlayer(level);
            }
        }
        else
        {
            if (isMonster(level, h + n, w) || isBoss(level, h + n, w))
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
                while (clock() < start + 20000)
                {
                }
            }
            if (isPerson(level, h + n, w))
            {
                dmgPlayer(level);
                break;
            }
        }
        else
        {
            if (isMonster(level, h + n, w) || isBoss(level, h + n, w))
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
                while (clock() < start + 20000)
                {
                }
            }
            if (isPerson(level, h, w + n))
            {
                dmgPlayer(level);
            }
        }
        else
        {
            if (isMonster(level, h, w + n) || isBoss(level, h, w + n))
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
                while (clock() < start + 20000)
                {
                }
            }
            if (isPerson(level, h, w + n))
            {
                dmgPlayer(level);
                break;
            }
        }
        else
        {
            if (isMonster(level, h, w + n) || isBoss(level, h, w + n))
            {
                dmgMonster(level, h, w + n);
                break;
            }
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

    if (hasWeapon(m))
    {
        monsterShoot(level, m, way);
    }
    else
    {
        // move in direction of the player
        boolean takeDirection = directionTakenMonster(level, m, way);
        while (!takeDirection)
        {
            way = (way + 1) % 4;
            takeDirection = directionTakenMonster(level, m, way);
        }
    }

    // mark 'M' if next point is empty
    if (isBlank(level, m->p.h, m->p.w))
    {
        level->currentRoom->map[m->p.h][m->p.w] = 'M';
    }
}

void randomMovedMonster(Level *level, Monster *m)
{
    int way = rand() % 4;
    switch (way)
    {
        {
        case North:
            if (noObstacle(level, m->p.h - 1, m->p.w))
            {
                m->p.h -= 1;
            }
            break;

        case East:
            if (noObstacle(level, m->p.h, m->p.w + 1))
            {
                m->p.w += 1;
            }
            break;

        case South:
            if (noObstacle(level, m->p.h + 1, m->p.w))
            {
                m->p.h += 1;
            }
            break;

        case West:
            if (noObstacle(level, m->p.h, m->p.w - 1))
            {
                m->p.w -= 1;
            }
            break;
        }
    }
}

void monsterShoot(Level *level, Monster *m, direction way)
{
    int h = m->p.h;
    int w = m->p.w;
    if (m->ss)
    {
        switch (way)
        {
        case North:
            upSS(level, h, w);
            break;

        case West:
            leftSS(level, h, w);
            break;

        case South:
            downSS(level, h, w);
            break;

        case East:
            rightSS(level, h, w);
            break;
        }
    }
    else
    {
        switch (way)
        {
        case North:
            upShoot(level, h, w);
            break;

        case West:
            leftShoot(level, h, w);
            break;

        case South:
            downShoot(level, h, w);
            break;

        case East:
            rightShoot(level, h, w);
            break;
        }
    }
    // movement aléatoire du monstre
    randomMovedMonster(level, m);
}

void restlessMonsters(Level *level)
{
    /*
    if (isType(level, level->coord.u, level->coord.v, "Room"))
    {
        MonsterList *monsters = level->currentRoom->monsters;
        if (monsters->size)
        {
            // printf("=======monsters: %p, size: %d, list[1]: %p=========", monsters, monsters->size, monsters->list[1]);
            lockDoors(level, level->coord.u, level->coord.v);
            for (int i = 0; i < monsters->size; i += 1)
            {
                movedMonster(level, monsters->list[i]);
                sideAttack(level, monsters->list[i]);
            }
        }
        else
        {
            unlockDoors(level, level->coord.u, level->coord.v);
        }
    }
    */
    if (isType(level, level->coord.u, level->coord.v, "Boss"))
    {
        MonsterList *boss = level->currentRoom->monsters;
        if (boss->size)
        {
            printf("=======monster hp: %.2f =========", boss->list[0]->hpMax);
            lockDoors(level, level->coord.u, level->coord.v);
            bossAttack(level, boss->list[0]);
        }
        else
        {
            unlockDoors(level, level->coord.u, level->coord.v);
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

// Boss Level 1: Jagger
// 100 hpMax | shoot=true | Tire et se déplace AUSSI vers le joueur

void bossAttack(Level *level, Monster *m)
{

    // current point
    if (level->currentRoom->map[m->p.h][m->p.w] == 'B')
    {
        level->currentRoom->map[m->p.h][m->p.w] = ' ';
    }
    if (isSpike(level, m->p.h, m->p.w))
    {
        // loose 0.5 hp if the point of the player is 'S'
        ouch(level->player, 0.5);
    }

    int h = m->p.h;
    int w = m->p.w;
    // shoot direction
    direction way = directionToTakeMonster(level, m);
    switch (way)
    {
    case North:
        upShoot(level, h, w);
        break;

    case West:
        leftShoot(level, h, w);
        break;

    case South:
        downShoot(level, h, w);
        break;

    case East:
        rightShoot(level, h, w);
        break;
    }

    // move on direction of the player
    boolean takeDirection = directionTakenMonster(level, m, way);
    while (!takeDirection)
    {
        way = (way + 1) % 4;
        takeDirection = directionTakenMonster(level, m, way);
    }

    // mark 'B' if next point is empty
    if (isBlank(level, m->p.h, m->p.w))
    {
        level->currentRoom->map[m->p.h][m->p.w] = 'B';
    }

    // attack when boss is next to the player
    sideAttack(level, m);
}
