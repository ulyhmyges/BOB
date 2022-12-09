/*
**  Filename : level.c
**
**  Made by : HT
**
**  Description : model of a level of the bob's game
*/

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
        r->map[r->rows / 2][r->columns / 2] = kind; // le boss (B) au milieu de la pièce
        break;

    case 'I': // item room et item room bonus
        r = newRoom(rows, columns, "Item", 0, monsterfile);
        r->map[r->rows / 2][r->columns / 2] = kind; // l'item (I) au milieu de la pièce
        r->item = itemList->list[itemIndex];
        break;

    default:
        r = newRoom(rows, columns, "Spawner", 0, monsterfile);
        r->map[r->rows / 2][r->columns / 2] = kind; // le player (P) au milieu de la pièce
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
    level->map = newMap(7, 7); // car level->height = 7 et level->width = 7
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
    // création de la grille de rooms de type 'Wall' représentant l'étage
    createFloor(level, monsterfile);

    // création special rooms
    level->spawner = createSpecialRoom(level->rows, level->columns, 'P', itemfile, monsterfile);
    level->bossRoom = createSpecialRoom(level->rows, level->columns, 'B', itemfile, monsterfile);
    level->itemRoom = createSpecialRoom(level->rows, level->columns, 'I', itemfile, monsterfile);
    level->itemRoomBonus = createSpecialRoom(level->rows, level->columns, 'I', itemfile, monsterfile);

    level->character = 'P';

    // direction par défaut
    level->direction = North;

    // place le spawner au centre de l'étage
    level->u = level->height / 2;
    level->v = level->width / 2;
    updateFloor(level, level->u, level->v, *level->spawner);
    updateMap(level->map, level->u, level->v, level->map->spawn);
    // pièce actuelle
    level->room = level->spawner;

    randFloor(level, roomfile, monsterfile); // placement aléatoire des pièces à partir du Spawner
    addItemRoom(level, level->itemRoom);     // ajout de l'item room
    putAllDoors(level);
    return level;
}

void randFloor(Level *level, char *roomfile, char *monsterfile)
{

    RoomList *roomList = readRoomFile(roomfile, monsterfile);

    int count = 0;
    while (count < 10)
    {

        int index = 0;
        level->u = level->height / 2;
        level->v = level->width / 2;
        int times = 0;
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
    }
    addBossRoom(level);
    putItemRoom(level, level->u, level->v, level->itemRoomBonus); // ajout item room bonus
    strcpy(level->itemRoomBonus->type, "Bonus");
    updateMap(level->map, level->u, level->v, level->map->bonus);
}

int addBossRoom(Level *level)
{
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

int addItemRoomBonus(Level *level)
{
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
    level->u = i;
    level->v = j;
    if (i > 0 && level->map->grid[i - 1][j] == '0')
    {
        level->u -= 1;
        updateFloor(level, i - 1, j, *room);
        updateMap(level->map, i - 1, j, level->map->item);
        return 1;
    }
    if (j < level->width - 1 && level->map->grid[i][j + 1] == '0')
    {
        level->v += 1;
        updateFloor(level, i, j + 1, *room);
        updateMap(level->map, i, j + 1, level->map->item);
        return 1;
    }
    if (i < level->height - 1 && level->map->grid[i + 1][j] == '0')
    {
        level->u += 1;
        updateFloor(level, i + 1, j, *room);
        updateMap(level->map, i + 1, j, level->map->item);
        return 1;
    }
    if (j > 0 && level->map->grid[i][j - 1] == '0')
    {
        level->v -= 1;
        updateFloor(level, i, j - 1, *room);
        updateMap(level->map, i, j - 1, level->map->item);
        return 1;
    }
    return 0;
}

void northDoor(Level *level, int u, int v, char door)
{
    level->floor[u][v].map[0][level->floor[u][v].columns / 2] = door;
    // room->map[0][room->columns / 2] = door;
}

void eastDoor(Level *level, int u, int v, char door)
{
    level->floor[u][v].map[level->floor[u][v].rows / 2][level->floor[u][v].columns - 1] = door;
    // room->map[room->rows / 2][room->columns - 1] = door;
}

void southDoor(Level *level, int u, int v, char door)
{
    level->floor[u][v].map[level->floor[u][v].rows - 1][level->floor[u][v].columns / 2] = door;
    // room->map[room->rows - 1][room->columns / 2] = door;
}

void westDoor(Level *level, int u, int v, char door)
{
    level->floor[u][v].map[level->floor[u][v].rows / 2][0] = door;
    // room->map[room->rows / 2][0] = door;
}

void putAllDoors(Level *level)
{
    for (int i = 0; i < level->height; i += 1)
    {
        for (int j = 0; j < level->width; j += 1)
        {
            if (!isType(level, i, j, "Wall"))
            {
                putCadinalDoors(level, i, j);
            }
        }
    }
}

void putCadinalDoors(Level *level, int i, int j)
{
    // east door
    if (j < level->width - 1)
    {
        if (isKind(level, i, j + 1, 'r'))
        {
            eastDoor(level, i, j, 'D');
        }
        if (isKind(level, i, j + 1, 'I'))
        {
            eastDoor(level, i, j, '$');
            printf("east door $$$$");
        }
        if (isKind(level, i, j + 1, 'B'))
        {
            eastDoor(level, i, j, 'B');
        }
    }
    else
    {
        eastDoor(level, i, j, 'W');
    }

    // south door
    if (i < level->height - 1)
    {
        if (isKind(level, i + 1, j, 'r'))
        {
            southDoor(level, i, j, 'D');
        }
        if (isKind(level, i + 1, j, 'I'))
        {
            southDoor(level, i, j, '$');
            printf("south door $$$$");
        }
        if (isKind(level, i + 1, j, 'B'))
        {
            southDoor(level, i, j, 'B');
        }
    }
    else
    {
        southDoor(level, i, j, 'W');
    }

    // west door
    if (j > 0)
    {
        if (isKind(level, i, j - 1, 'r'))
        {
            westDoor(level, i, j, 'D');
        }
        if (isKind(level, i, j - 1, 'I'))
        {
            westDoor(level, i, j, '$');
            printf("west door $$$$");
        }
        if (isKind(level, i, j - 1, 'B'))
        {
            westDoor(level, i, j, 'B');
        }
    }
    else
    {
        westDoor(level, i, j, 'W');
    }

    // north door
    if (i > 0)
    {
        if (isKind(level, i - 1, j, 'r'))
        {
            northDoor(level, i, j, 'D');
        }
        if (isKind(level, i - 1, j, 'I'))
        {
            northDoor(level, i, j, '$');
            printf("north door $$$");
        }
        if (isKind(level, i - 1, j, 'B'))
        {
            northDoor(level, i, j, 'B');
        }
    }
    else
    {
        northDoor(level, i, j, 'W');
    }
}

int isType(Level *level, int u, int v, char *type)
{
    return !strcmp(level->floor[u][v].type, type);
}

int isKind(Level *level, int u, int v, char kind)
{
    return level->map->grid[u][v] == kind;
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
            printf("\n%d-%d ++++++++++++++++\n", i, j);
            showRoom(level->floor[i][j]);
        }
        printf("------------\n");
    }
}
