/*
**  Filename : map.h
**
**  Made by : HT
**
**  Description : model about a map of the floor
*/

#ifndef MAP_H

#define MAP_H

typedef struct Map {
    int height;
    int width;
    char **grid;
    char room;      //r
    char item;      //i
    char bonus;     //b
    char boss;      //B
    char spawn;     //s
} Map;

Map * newMap(int height, int width);
void freeMap(Map *map);
void showMap(Map map);
void updateMap(Map *map, int i, int j, char c);

#endif // MAP_H