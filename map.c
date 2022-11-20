#include <stdio.h>
#include <stdlib.h>
#include "map.h"

Map *newMap(int height, int width)
{
    Map *map = malloc(sizeof(Map));
    map->height = height;
    map->width = width;
    map->room = 'r';
    map->item = 'I';
    map->spawn = 'S';
    map->bonus = 'J';
    map->boss = 'B';
    map->grid = malloc(sizeof(char *) * map->height);
    for (int i = 0; i < map->height; i += 1)
    {
        map->grid[i] = malloc(sizeof(char) * map->width);
    }
    for (int i = 0; i < map->height; i += 1){
        for (int j = 0; j < map->width; j += 1){
            map->grid[i][j] = '0';
        }
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
    printf("\n--------map--------\n");
    for (int i = 0; i < map.height; i += 1){
        for (int j= 0; j < map.width; j += 1){
            printf("%c", map.grid[i][j]);
        }
        printf("\n");
    }
    printf("--------map--------\n");
}

void updateMap(Map *map, int i, int j, char c){
    map->grid[i][j] = c;
}