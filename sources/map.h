/*
**  Filename : map.h
**
**  Made by : HT
**
**  Description : model about a map of the floor
*/

#ifndef MAP_H

#define MAP_H

typedef struct Point {
    int h;
    int w;
} Point;

typedef struct Map {
    int height;
    int width;
    char **grid;
    char room;      //r
    char item;      //I
    char bonus;     //J
    char boss;      //B
    char spawn;     //S
    char wall;      //0
} Map;

Map * newMap(int height, int width);
void freeMap(Map *map);
void showMap(Map map);

#endif // MAP_H