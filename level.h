#ifndef FLOOR_H

#define FLOOR_H
#include "room.h"
#include "map.h"

typedef enum Direction
{
    North,
    East,
    South,
    West
} Direction;

typedef struct Level
{
    int id;
    Room **floor;
    int height; // 7
    int width;  // 7

    Direction direction;
    Map *map;

    char character; // P
    int u;
    int v;
    Room *room;
    int rows;
    int columns;
    Room *spawner;
    Room *itemRoom;
    Room *itemRoomBonus;
    Room *bossRoom;
} Level;

Room *createSpecialRoom(int rows, int columns, char kind);
Level *newLevel(int id, int rows, int columns);
void freeLevel(Level *level);
void updateFloor(Room **floor, int i, int j, Room r);
int getU(Level *level);
int getV(Level *level);
void randFloor(Level *level);
int addBossRoom(Level *level);
int addItemRoom(Level *level);
int putItemRoom(Level *level, int i, int j);

#endif // FLOOR_H