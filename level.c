#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "level.h"

/**
 * @brief Create a Special Room object:
 * a ItemRoom/ItemRoomBonus (I)
 * or a Spawner (P)
 * or a BossRoom (B)
 *
 * @param rows
 * @param columns
 * @param kind I, P or B
 * @return Room*
 */
Room *createSpecialRoom(int rows, int columns, char kind)
{
    Room *r = NULL;
    switch (kind)
    {
    case 'B':
        r = newRoom(rows, columns, 3);
        r->map[r->rows / 2][r->columns / 2] = kind;

    default:
        r = newRoom(rows, columns, 0);
        r->map[r->rows / 2][r->columns / 2] = kind;
    }
    return r;
}

Level *newLevel(int id, int rows, int columns)
{
    Level *level = malloc(sizeof(Level));
    level->id = id;
    level->height = 7;
    level->width = 7;
    level->rows = rows;
    level->columns = columns;

    // création d'une grille de Room
    level->floor = malloc(sizeof(Room *) * level->height);
    for (int i = 0; i < level->height; i += 1)
    {
        level->floor[i] = malloc(sizeof(Room) * level->width);
    }
    // création de la map
    level->map = newMap(7, 7);

    // création room du personnage 'P'
    level->room = newRoom(level->rows, level->columns, 0);
    level->character = 'P';

    // création special rooms
    level->spawner = createSpecialRoom(level->rows, level->columns, 'P');
    level->itemRoom = createSpecialRoom(level->rows, level->columns, 'I');
    level->itemRoomBonus = createSpecialRoom(level->rows, level->columns, 'I');
    level->bossRoom = createSpecialRoom(level->rows, level->columns, 'B');

    // direction par défaut
    level->direction = North;

    // spawner au centre de l'étage
    level->u = level->height / 2;
    level->v = level->width / 2;
    updateFloor(level->floor, level->u, level->v, *level->spawner);
    updateMap(level->map, level->u, level->v, level->map->spawn);

    return level;
}

void randFloor(Level *level)
{
    int count = 0;
    int essai = 0;
    int times = 0;
    srand(time(NULL));
    while (essai < 5 )
    {
        while (count < 10 && times < 50)
        {
            level->direction = rand() % 4;
            int design = rand() % 5;
            design += 1;
            printf("direction: %d\n count: %d", level->direction, count);
            switch (level->direction)
            {
            case North:
                if (level->u > 0 && level->map->grid[level->u - 1][level->v] == '0')
                {
                    level->u -= 1;
                    count += 1;
                    break;
                }

            case East:
                if (level->v < level->width - 1 && level->map->grid[level->u][level->v + 1] == '0')
                {
                    level->v += 1;
                    count += 1;
                    break;
                }

            case South:
                if (level->u < level->height - 1 && level->map->grid[level->u + 1][level->v] == '0')
                {
                    level->u += 1;
                    count += 1;
                    break;
                }

            case West:
                if (level->v > 0 && level->map->grid[level->u][level->v - 1] == '0')
                {
                    level->v -= 1;
                    count += 1;
                    break;
                }
            }
            Room *room = newRoom(level->rows, level->columns, design);
            updateFloor(level->floor, level->u, level->v, *room);
            updateMap(level->map, level->u, level->v, 'r');
            times += 1;
        }
        essai += 1;
    }
    addBossRoom(level);
    putItemRoom(level, level->u, level->v);
}

int addBossRoom(Level *level)
{
    int design = rand() % 5;
    design += 1;
    if (level->u > 0 && level->map->grid[level->u - 1][level->v] == '0')
    {
        level->u -= 1;
        Room *r = newRoom(level->rows, level->columns, design);
        updateFloor(level->floor, level->u, level->v, *r);
        freeRoom(r);
        updateMap(level->map, level->u, level->v, level->map->boss);
        return 1;
    }
    if (level->v < level->width - 1 && level->map->grid[level->u][level->v + 1] == '0')
    {
        level->v += 1;
        Room *r = newRoom(level->rows, level->columns, design);
        updateFloor(level->floor, level->u, level->v, *r);
        freeRoom(r);
        updateMap(level->map, level->u, level->v, level->map->boss);
        return 1;
    }
    if (level->u < level->height - 1 && level->map->grid[level->u + 1][level->v] == '0')
    {
        level->u += 1;
        Room *r = newRoom(level->rows, level->columns, design);
        updateFloor(level->floor, level->u, level->v, *r);
        freeRoom(r);
        updateMap(level->map, level->u, level->v, level->map->boss);
        return 1;
    }
    if (level->v > 0 && level->map->grid[level->u][level->v - 1] == '0')
    {
        level->v -= 1;
        Room *r = newRoom(level->rows, level->columns, design);
        updateFloor(level->floor, level->u, level->v, *r);
        freeRoom(r);
        updateMap(level->map, level->u, level->v, level->map->boss);
        return 1;
    }
    return 0;
}

int addItemRoom(Level *level)
{
    for (int i = 0; i < level->height; i += 1)
    {
        for (int j = 0; j < level->width; j += 1)
        {
            if (level->map->grid[i][j] == 'r')
            {
                if (putItemRoom(level, i, j))
                {
                    return 1;
                }
            }
        }
    }
    return 0;
}

int putItemRoom(Level *level, int i, int j)
{
    if (i > 0 && level->map->grid[i - 1][j] == '0')
    {
        Room *r = newRoom(level->rows, level->columns, 0);
        updateFloor(level->floor, i - 1, j, *r);
        freeRoom(r);
        updateMap(level->map, i - 1, j, level->map->item);
        return 1;
    }
    if (j < level->width - 1 && level->map->grid[i][j + 1] == '0')
    {
        Room *r = newRoom(level->rows, level->columns, 0);
        updateFloor(level->floor, i, j + 1, *r);
        freeRoom(r);
        updateMap(level->map, i, j + 1, level->map->item);
        return 1;
    }
    if (i < level->height - 1 && level->map->grid[i + 1][j] == '0')
    {
        Room *r = newRoom(level->rows, level->columns, 0);
        updateFloor(level->floor, i + 1, j, *r);
        freeRoom(r);
        updateMap(level->map, i + 1, j, level->map->item);
        return 1;
    }
    if (j > 0 && level->map->grid[i][j - 1] == '0')
    {
        Room *r = newRoom(level->rows, level->columns, 0);
        updateFloor(level->floor, i, j - 1, *r);
        freeRoom(r);
        updateMap(level->map, i, j - 1, level->map->item);
        return 1;
    }
    return 0;
}

int getU(Level *level)
{
    return level->u;
}
int getV(Level *level)
{
    return level->v;
}

void updateFloor(Room **floor, int i, int j, Room r)
{
    floor[i][j] = r;
}

void freeLevel(Level *level)
{
    freeRoom(level->bossRoom);
    freeRoom(level->itemRoomBonus);
    freeRoom(level->itemRoom);
    freeRoom(level->spawner);
    freeRoom(level->room);
    freeMap(level->map);
    for (int i = 0; i < level->height; i += 1)
    {
        free(level->floor[i]);
    }
    free(level->floor);
    free(level);
}
