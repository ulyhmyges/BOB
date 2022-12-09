/*
**  Filename : level.h
**
**  Made by : HT
**
**  Description : model of a level of the bob's game
*/

#ifndef FLOOR_H

#define FLOOR_H
#include "room.h"
#include "map.h"

typedef enum direction
{
    North,
    East,
    South,
    West
} direction;

typedef struct Level
{
    int id;
    Room **floor;
    int height; // 7 par défaut
    int width;  // 7
    direction direction;
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
void randFloor(Level *level, char *roomfile, char *monsterfile);
void putAllDoors(Level *level);
void putCadinalDoors(Level *level, int i, int j);
int isType(Level *level, int u , int v, char *type);
int isKind(Level *level, int u, int v, char kind);
void northDoor(Level *level, int u, int v, char door);
void eastDoor(Level *level, int u, int v, char door);
void southDoor(Level *level, int u, int v, char door);
void westDoor(Level *level, int u, int v, char door);
int addBossRoom(Level *level);
int addItemRoomBonus(Level *level);

int addItemRoom(Level *level, Room *room);
int putItemRoom(Level *level, int i, int j, Room *room);

#endif // FLOOR_H