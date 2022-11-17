#ifndef FLOOR_H

#define FLOOR_H
#include "room.h"
#include "map.h"

typedef struct Level
{
    int id;
    Room **floor;
    int height;  // 7
    int width; // 7
    char direction;
    Map *map;

    char character; // P
    int u;
    int v;
    Room *room;
    Room *spawner;
    Room *itemRoom;
    Room *itemRoomBonus;
    Room *bossRoom;
} Level;

Room *createSpecialRoom(int rows, int columns, char kind);
Level *newLevel(int id, int rows, int columns);
void freeLevel(Level *level);

#endif // FLOOR_H