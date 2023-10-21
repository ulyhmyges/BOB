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

typedef struct Point {
    int h;
    int w;
} Point;

typedef struct Position {
    int u; // vertical coordinates du personnage 'P' à l'étage
    int v; // horizontal coordinates du personnage 'P'
    Point p;
} Position;

typedef struct Level
{
    int id;
    Room **floor; // une grille de rooms
    int height; // 7 par défaut
    int width;  // 7
    direction direction;
    Map *map;
    char character; // P
    // int u;  
    // int v;  
    Position coord;
    Room *currentRoom;
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
void updateFloor(Level *level, int i, int j, Room* r);
void showFloor(Level *level);
void randFloor(Level *level, char *roomfile, char *monsterfile);
void putAllDoors(Level *level);
int isKind(Level *level, int u, int v, char kind);
void northDoor(Level *level, int u, int v, char door);
void eastDoor(Level *level, int u, int v, char door);
void southDoor(Level *level, int u, int v, char door);
void westDoor(Level *level, int u, int v, char door);
int addBossRoom(Level *level);


int addItemRoom(Level *level, Room *room);
int putItemRoom(Level *level, int i, int j, Room *room);

int isType(Level *level, int h, int w, char *type);
char** copyMapRoom(Room room);
void putCardinalDoors(Level* level, int h, int w);
void putEastDoor(Level* level, int h, int w);
void putSouthDoor(Level*  level, int h, int w);
void putWestDoor(Level* level, int h, int w);
void putNorthDoor(Level* level, int h, int w);

void updateMapLevel(Level* level, int i, int j, char kind);

#endif // FLOOR_H