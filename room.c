#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
    strcpy(r->objects, "RGSH");
    r->map = malloc(sizeof(char *) * r->rows);
    for (int i = 0; i < r->rows; i += 1)
    {
        r->map[i] = malloc(sizeof(char) * r->columns);
    }
    //
    wallBorders(r);

    // rochers 3 x 3 au centre de la pièce
    putThing(r, r->objects[0], 3, r->rows / 2 - 1, r->columns / 2 - 1);

    // gaps aux coins supérieurs de la pièce
    putThing(r, r->objects[1], 2, 1, 1);
    r->map[1][1] = ' ';
    putThing(r, r->objects[1], 2, 1, r->columns - 3);
    r->map[1][r->columns-2] = ' ';
    
    // gaps aux coins inférieurs de la pièce
    putThing(r, r->objects[1], 2, r->rows - 3, 1);
    r->map[r->rows-2][1] = ' ';
    putThing(r, r->objects[1], 2, r->rows - 3, r->columns - 3);
    r->map[r->rows-2][r->columns-2] = ' ';

    return r;
}

void setThing(Room *r, char thing, int row, int column)
{
    r->map[row][column] = thing;
}

/**
 * @brief dispose des objets thing sous forme d'un carré
 * dans la pièce si toutes les contraintes sont respectées
 *
 * @param r la pièce
 * @param thing l'objet à disposer dans la pièce
 * @param pow la longueur du carré d'objets
 * @param row indice de la ligne
 * @param column indice de la colonne
 */
void putThing(Room *r, char thing, int pow, int row, int column)
{
    for (int i = row; i < row + pow && i < r->rows - 1; i += 1)
    {
        for (int j = column; j < column + pow && j < r->columns - 1; j += 1)
        {
            if (i > 0 && i < r->rows - 1 && j > 0 && j < r->columns - 1)
            {
                r->map[i][j] = thing;
            }
        }
    }
}

/**
 * @brief Construction des bordures de la pièce r du Donjon
 *
 * @param r
 */
void wallBorders(Room *r)
{
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