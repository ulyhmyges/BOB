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

#endif // MAP_H