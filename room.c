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
    // strcpy(r->objects, "RGSH");
    r->rock = 'R';
    r->gap = 'G';
    r->spike = 'S';
    r->health = 'H';
    r->map = malloc(sizeof(char *) * r->rows);
    for (int i = 0; i < r->rows; i += 1)
    {
        r->map[i] = malloc(sizeof(char) * r->columns);
    }
    wallBorders(r); // construction des murs et portes de la pièce
    designRoom5(r); // construction de l'intérieur de la pièce

    return r;
}
/**
 * @brief dessine l'intérieur de la pièce selon le modèle suivant :
 * WWWWWWWDWWWWWWW
 * WHG         G W
 * WGG         GGW
 * W     RRR     W
 * D     RRR     D
 * W     RRR     W
 * WGG         GGW
 * W G         GHW
 * WWWWWWWDWWWWWWW
 *
 * @param r la pièce
 */
void designRoom1(Room *r)
{
    // rochers 3 x 3 au centre de la pièce
    putThing(r, r->rock, 3, r->rows / 2 - 1, r->columns / 2 - 1, 1, 1);

    // gaps aux coins supérieurs de la pièce
    putThing(r, r->gap, 2, 1, 1, 1, 1);
    r->map[1][1] = 'H';
    putThing(r, r->gap, 2, 1, r->columns - 3, 1, 1);
    r->map[1][r->columns - 2] = ' ';

    // gaps aux coins inférieurs de la pièce
    putThing(r, r->gap, 2, r->rows - 3, 1, 1, 1);
    r->map[r->rows - 2][1] = ' ';
    putThing(r, r->gap, 2, r->rows - 3, r->columns - 3, 1, 1);
    r->map[r->rows - 2][r->columns - 2] = 'H';
}

/**
 * @brief dessine l'intérieur de la pièce selon le modèle suivant :
 * WWWWWWWDWWWWWWW
 * WHG         G W
 * WGG         GGW
 * W   S R R S   W
 * D             D
 * W   S R R S   W
 * WGG         GGW
 * W G         GHW
 * WWWWWWWDWWWWWWW
 *
 * @param r
 */
void designRoom2(Room *r)
{
    // obstacles au centre de la pièce
    putThing(r, r->spike, 3, r->rows / 2 - 1, r->columns / 2 - 3, 2, 2);
    putThing(r, r->spike, 3, r->rows / 2 - 1, r->columns / 2 + 1, 2, 2);
    putThing(r, r->rock, 3, r->rows / 2 - 1, r->columns / 2 - 1, 2, 2);

    // gaps aux coins supérieurs de la pièce
    putThing(r, r->gap, 2, 1, 1, 1, 1);
    r->map[1][1] = 'H';
    putThing(r, r->gap, 2, 1, r->columns - 3, 1, 1);
    r->map[1][r->columns - 2] = ' ';

    // gaps aux coins inférieurs de la pièce
    putThing(r, r->gap, 2, r->rows - 3, 1, 1, 1);
    r->map[r->rows - 2][1] = ' ';
    putThing(r, r->gap, 2, r->rows - 3, r->columns - 3, 1, 1);
    r->map[r->rows - 2][r->columns - 2] = 'H';
}

/**
 * @brief dessine l'intérieur de la pièce selon le modèle suivant :
 * WWWWWWWDWWWWWWW
 * W             W
 * W             W
 * W   RRR RRR   W
 * D             D
 * W   RRR RRR   W
 * W             W
 * W             W
 * WWWWWWWDWWWWWWW
 * @param r
 */
void designRoom3(Room *r)
{
    // obstacles au centre de la pièce
    putThing(r, r->rock, 3, r->rows / 2 - 1, r->columns / 2 - 3, 2, 1);
    putThing(r, r->rock, 3, r->rows / 2 - 1, r->columns / 2 + 1, 2, 1);
}

/**
 * @brief dessine l'intérieur de la pi!ce selon le modèle suivant :
 * WWWWWWWDWWWWWWW
 * W             W
 * W             W
 * W      S      W
 * D     SHS     D
 * W      S      W
 * W             W
 * W             W
 * WWWWWWWDWWWWWWW
 * 
 * @param r la pièce
 */
void designRoom4(Room *r)
{
    putThing(r, r->spike, 3, r->rows / 2 - 1, r->columns / 2 - 1, 1, 1);
    putThing(r, ' ', 3, r->rows / 2 - 1, r->columns / 2 - 1, 2, 2);
    putThing(r, r->health, 1, r->rows / 2, r->columns / 2, 1, 1);
}

/**
 * @brief dessine l'intérieur de la pi!ce selon le modèle suivant :
 * WWWWWWWDWWWWWWW
 * WG            W
 * W             W
 * W             W
 * D             D
 * W             W
 * W             W
 * W            GW
 * WWWWWWWDWWWWWWW
 * 
 * @param r 
 */
void designRoom5(Room *r)
{
    putThing(r, r->gap, 1, 1, 1, 1, 1);
    putThing(r, r->gap, 1, r->rows - 2, r->columns - 2, 1, 1);
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
void putThing(Room *r, char thing, int pow, int row, int column, int verticalIncrement, int horizontalIncrement)
{
    for (int i = row; i < row + pow && i < r->rows - 1; i += verticalIncrement)
    {
        for (int j = column; j < column + pow && j < r->columns - 1; j += horizontalIncrement)
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