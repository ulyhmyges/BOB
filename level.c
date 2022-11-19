#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "level.h"
#include "roomFile.h"
#include "itemFile.h"
#include "itemList.h"

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
Room *createSpecialRoom(int rows, int columns, char kind, char *itemfile, char *monsterfile)
{
    Room *r = NULL;
    ItemList *itemList = readItemFile(itemfile);
    int itemIndex = rand() % itemList->size;

    switch (kind)
    {
    case 'B': // boss room
        r = newRoom(rows, columns, "Boss", 3, monsterfile);
        r->map[r->rows / 2][r->columns / 2] = kind;
        break;

    case 'I': // item room
        r = newRoom(rows, columns, "Item", 0, monsterfile);
        r->map[r->rows / 2][r->columns / 2] = kind;
        r->item = itemList->list[itemIndex];
        break;

    default:
        r = newRoom(rows, columns, "Spawner", 0, monsterfile);
        r->map[r->rows / 2][r->columns / 2] = kind;
    }
    return r;
}
/**
 * @brief Procédure
 * création d'une grille représentant l'étage
 * création de la map de l'étage
 *
 * @param level objet complexe représentant l'étage
 */
void createFloor(Level *level, char *monsterfile)
{
    level->floor = malloc(sizeof(Room *) * level->height);
    for (int i = 0; i < level->height; i += 1)
    {
        level->floor[i] = malloc(sizeof(Room) * level->width);
    }
    for (int i = 0; i < level->height; i += 1)
    {
        for (int j = 0; j < level->width; j += 1)
        {
            level->floor[i][j] = *newRoom(level->rows, level->columns, "Wall", 6, monsterfile);
        }
    }
    // création de la map
    level->map = newMap(7, 7);
}

Level *newLevel(int id, int rows, int columns, char *roomfile, char *itemfile, char *monsterfile)
{
    srand(time(NULL));
    Level *level = malloc(sizeof(Level));
    level->id = id;
    level->height = 7;
    level->width = 7;
    level->rows = rows;
    level->columns = columns;
    createFloor(level, monsterfile);

    // création special rooms
    level->spawner = createSpecialRoom(level->rows, level->columns, 'P', itemfile, monsterfile);
    level->bossRoom = createSpecialRoom(level->rows, level->columns, 'B', itemfile, monsterfile);
    level->itemRoom = createSpecialRoom(level->rows, level->columns, 'I', itemfile, monsterfile);
    level->itemRoomBonus = createSpecialRoom(level->rows, level->columns, 'I', itemfile, monsterfile);

    // pièce actuelle
    level->room = level->spawner;
    level->character = 'P';

    // direction par défaut
    level->direction = North;

    // spawner au centre de l'étage
    level->u = level->height / 2;
    level->v = level->width / 2;
    // place le spawner au centre de l'étage
    updateFloor(level, level->u, level->v, *level->spawner);
    updateMap(level->map, level->u, level->v, level->map->spawn);
    // placement aléatoire des pièces
    randFloor(level, roomfile, monsterfile);
    addItemRoom(level, level->itemRoom);
    return level;
}

void randFloor(Level *level, char *roomfile, char *monsterfile)
{
    int count = 0;
    int essai = 0;
    int times = 0;
    RoomList *roomList = readRoomFile(roomfile, monsterfile);

    while (essai < 5)
    {
        int index = 0;
        while (count < 10 && times < 20)
        {
            level->direction = rand() % 4;
            int design = rand() % 5;
            design += 1;
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

            Room *room = roomList->list[index];
            updateFloor(level, level->u, level->v, *room);
            updateMap(level->map, level->u, level->v, 'r');
            times += 1;
            index = rand() % roomList->size;
        }
        essai += 1;
    }
    printf("u: %d ; v: %d\n", level->u, level->v);
    addBossRoom(level);
    printf("u: %d ; v: %d\n", level->u, level->v);
    putItemRoom(level, level->u, level->v, level->itemRoomBonus);
    printf("u: %d ; v: %d\n", level->u, level->v);
    strcpy(level->itemRoomBonus->type, "Bonus");
}

int addBossRoom(Level *level)
{
    int design = rand() % 5;
    design += 1;
    if (level->u > 0 && level->map->grid[level->u - 1][level->v] == '0')
    {
        level->u -= 1;
        updateFloor(level, level->u, level->v, *level->bossRoom);
        updateMap(level->map, level->u, level->v, level->map->boss);
        return 1;
    }
    if (level->v < level->width - 1 && level->map->grid[level->u][level->v + 1] == '0')
    {
        level->v += 1;
        updateFloor(level, level->u, level->v, *level->bossRoom);
        updateMap(level->map, level->u, level->v, level->map->boss);
        return 1;
    }
    if (level->u < level->height - 1 && level->map->grid[level->u + 1][level->v] == '0')
    {
        level->u += 1;
        updateFloor(level, level->u, level->v, *level->bossRoom);
        updateMap(level->map, level->u, level->v, level->map->boss);
        return 1;
    }
    if (level->v > 0 && level->map->grid[level->u][level->v - 1] == '0')
    {
        level->v -= 1;
        updateFloor(level, level->u, level->v, *level->bossRoom);
        updateMap(level->map, level->u, level->v, level->map->boss);
        return 1;
    }
    return 0;
}

int addItemRoomBonus(Level *level){
    // à faire
    return 0;
}

int addItemRoom(Level *level, Room *room)
{
    for (int i = 0; i < level->height; i += 1)
    {
        for (int j = 0; j < level->width; j += 1)
        {
            if (level->map->grid[i][j] == 'r')
            {
                if (putItemRoom(level, i, j, room))
                {
                    return 1;
                }
            }
        }
    }
    return 0;
}

int putItemRoom(Level *level, int i, int j, Room *room)
{
    if (i > 0 && level->map->grid[i - 1][j] == '0')
    {
        updateFloor(level, i - 1, j, *room);
        updateMap(level->map, i - 1, j, level->map->item);
        return 1;
    }
    if (j < level->width - 1 && level->map->grid[i][j + 1] == '0')
    {
        updateFloor(level, i, j + 1, *room);
        updateMap(level->map, i, j + 1, level->map->item);
        return 1;
    }
    if (i < level->height - 1 && level->map->grid[i + 1][j] == '0')
    {
        updateFloor(level, i + 1, j, *room);
        updateMap(level->map, i + 1, j, level->map->item);
        return 1;
    }
    if (j > 0 && level->map->grid[i][j - 1] == '0')
    {
        updateFloor(level, i, j - 1, *room);
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

void updateFloor(Level *level, int i, int j, Room r)
{
    level->floor[i][j] = r;
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

void showFloor(Level *level)
{
    for (int i = 0; i < level->height; i += 1)
    {
        for (int j = 0; j < level->width; j += 1)
        {
            showRoom(level->floor[i][j]);
        }
    }
}
