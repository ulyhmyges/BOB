
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
        printf("monster: %d, %d,----", monsters->list[i]->p.h, monsters->list[i]->p.w);
        if ((monsters->list[i]->p.h == h) && (monsters->list[i]->p.w == w))
        {
            printf("hpMax= %.1f---champion?: %d---", monsters->list[i]->hpMax, monsters->list[i]->champion);

            if (touched(monsters->list[i], level->player->dmg) == 0)
            {
                printf("hpMax= %.1f---", monsters->list[i]->hpMax);
                level->currentRoom->map[monsters->list[i]->p.h][monsters->list[i]->p.w] = ' ';
                removeMonsterByIndex(i, monsters);
            }
            else
            {
                printf("hpMax= %.1f---champion: %d---", monsters->list[i]->hpMax, monsters->list[i]->champion);
            }
        }
    }
}

boolean isClear(Level *level, int h, int w)
{
    return !(
        isWall(level, h, w) || isRock(level, h, w) || isMonster(level, h, w));
}

void shoot(Level *level, char letter)
{
    int n = 1;
    int h = level->coord.p.h;
    int w = level->coord.p.w;
    switch (letter)
    {
    case 'o':
        printf("P position (h,w): (%d,%d)", h, w);

        while ((h - n) > 0)
        {
            if (isClear(level, h - n, w))
            {
                if (!isGap(level, h - n, w))
                {
                    level->currentRoom->map[h - n][w] = '|';
                    showCurrentRoom(level);
                    clock_t start = clock();
                    while (clock() < start + 100000)
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
            if (!isGap(level, h - j, w))
            {
                level->currentRoom->map[h - j][w] = ' ';
                showCurrentRoom(level);
                clock_t start = clock();
                while (clock() < start + 100000)
                {
                }
            }
        }

        break;

    case 'k':
        break;
    case 'l':
        break;
    case 'm':
        break;
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
        if (isSafe(level, m->p.h - 1, m->p.w))
        {
            m->p.h -= 1;
            takeDirection = true;
        }
        break;

    case East:
        if (isSafe(level, m->p.h, m->p.w + 1))
        {
            m->p.w += 1;
            takeDirection = true;
        }
        break;

    case South:
        if (isSafe(level, m->p.h + 1, m->p.w))
        {
            m->p.h += 1;
            takeDirection = true;
        }
        break;
    case West:
        if (isSafe(level, m->p.h, m->p.w - 1))
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

    MonsterList *monsters = level->currentRoom->monsters;
    for (int i = 0; i < monsters->size; i += 1)
    {
        movedMonster(level, monsters->list[i]);
        sideAttack(level, monsters->list[i]);
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

boolean canShoot(Monster *m)
{
    return (m->shoot || m->ss);
}

boolean isSpectral(Monster *m)
{
    return m->ss;
}
