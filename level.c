#include <stdio.h>
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
    switch (kind)
    {
    case 'B':
        Room *room = newRoom(rows, columns, 3);
        room->map[room->rows / 2][room->columns / 2] = kind;

    default:
        Room *room = newRoom(rows, columns, 0);
        room->map[room->rows / 2][room->columns / 2] = kind;
    }
    return room;
}

Level *newLevel(int id, int rows, int columns)
{
    Level *level = malloc(sizeof(Level));
    level->id = id;
    level->height = 7;
    level->width = 7;

    // création d'une grille de Room
    level->floor = malloc(sizeof(Room *) * level->height);
    for (int i = 0; i < level->height; i += 1)
    {
        level->floor[i] = malloc(sizeof(Room) * level->width);
    }
    // création de la map
    level->map = newMap(7, 7);

    // création room du personnage 'P'
    level->room = newRoom(rows, columns, 0);
    level->character = 'P';

    // création special rooms
    level->spawner = createSpecialRoom(rows, columns, 'P');
    level->itemRoom = createSpecialRoom(rows, columns, 'I');
    level->itemRoomBonus = createSpecialRoom(rows, columns, 'I');
    level->bossRoom = createSpecialRoom(rows, columns, 'B');

    // default direction
    level->direction = 'N';
    return level;
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

