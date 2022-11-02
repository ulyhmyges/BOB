#include <stdio.h>
#include <stdlib.h>
#include "room.h"

/**
 * @brief permet de créer une pièce du Donjon
 *
 * @return Room*
 */
Room *newRoom(void)
{
    Room *r = malloc(sizeof(Room));
    r->rows = 9;
    r->columns = 15;
    r->map = malloc(sizeof(char *) * r->rows);
    for (int i = 0; i < r->rows; i += 1)
    {
        r->map[i] = malloc(sizeof(char) * r->columns);
    }
    wallBorders(r);
    return r;
}

void setThing(Room *r, char thing, int row, int column) {
    r->map[row][column] = thing;
}

/**
 * @brief Construction des bordures de la pièce r du Donjon
 * 
 * @param r 
 */
void wallBorders(Room *r) {
    for (int i = 0; i < r->rows; i += 1)
    {
        for (int j = 0; j < r->columns; j += 1)
        {
            // 1ère ligne et dernière ligne
            if (i == 0 || i == r->rows - 1)
            {
                if (j != r->columns / 2)
                {
                    r->map[i][j] = 'W';
                }
                else
                {
                    r->map[i][j] = 'D';
                }
            }
            // ligne du milieu
            else if (i == r->rows / 2)
            {
                if (j == 0 || j == r->columns - 1)
                {
                    r->map[i][j] = 'D';
                }
                else
                {
                    r->map[i][j] = ' ';
                }
            }
            // autres lignes
            else
            {
                if (j == 0 || j == r->columns - 1)
                {
                    r->map[i][j] = 'W';
                }
                else
                {
                    r->map[i][j] = ' ';
                }
            }
        }
    }
}

/**
 * @brief Affiche la pièce r
 * 
 * @param r 
 */
void showRoom(Room r)
{
    for (int i = 0; i < r.rows; i += 1)
    {
        for (int j = 0; j < r.columns; j += 1)
        {
            printf("%c", r.map[i][j]);
        }
        printf("\n");
    }
}

void freeRoom(Room *r)
{
    for (int i = 0; i < r->rows; i += 1)
    {
        free(r->map[i]);
    }
    free(r);
}