#include <stdio.h>
#include <stdlib.h>
#include "map.h"

Map *newMap(int height, int width)
{
    Map *map = malloc(sizeof(Map));
    map->height = height;
    map->width = width;
    map->room = 'r';
    map->item = 'i';
    map->spawn = 's';
    map->bonus = 'b';
    map->boss = 'B';
    map->grid = malloc(sizeof(char *) * map->height);
    for (int i = 0; i < map->height; i += 1)
    {
        map->grid[i] = malloc(sizeof(char) * map->width);
    }
    return map;
}

void freeMap(Map *map)
{
    for (int i = 0; i < map->height; i += 1)
    {
        free(map->grid[i]);
    }
    free(map->grid);
    free(map);
}

void showMap(Map map){
    for (int i = 0; i < map.height; i += 1){
        for (int j= 0; j < map.width; j += 1){
            printf("%c", map.grid[i][j]);
        }
        printf("\n");
    }
}