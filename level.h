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
    int height; // 7 par défaut
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

Room *createSpecialRoom(int rows, int columns, char kind, char *itemfile, char *monsterfile);
void createFloor(Level *level, char *monsterfile);
Level *newLevel(int id, int rows, int columns, char *roomfile, char *itemfile, char *monsterfile);
void freeLevel(Level *level);
void updateFloor(Level *level, int i, int j, Room r);
void showFloor(Level *level);
int getU(Level *level);
int getV(Level *level);
void randFloor(Level *level, char *fwd, char *monsterfile);
int addBossRoom(Level *level);
int addItemRoomBonus(Level *level);

int addItemRoom(Level *level, Room *room);
int putItemRoom(Level *level, int i, int j, Room *room);

#endif // FLOOR_H