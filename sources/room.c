/*
**  Filename : room.c
**
**  Made by : HT
**
**  Description : model of a rooms with useful functions
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "room.h"
#include "monsterFile.h"

/**
 * @brief permet de créer une pièce du Donjon
 *
 * @return Room*
 */
Room *newRoom(int rows, int columns, char *type, int design, char *monsterfile)
{
    Room *r = malloc(sizeof(Room));
    r->id = 0;
    r->type = malloc(sizeof(char) * 8);
    strcpy(r->type, type);
    r->rows = rows;
    r->columns = columns;
    r->rock = 'R';
    r->gap = 'G';
    r->spike = 'S';
    r->health = 'H';
    // r->item = malloc(sizeof(Item));
    r->item = newItem("Empty", 0, 0, 0, false, false, false);
    createMapRoom(r, design);
    createMonsterList(r, monsterfile);
    return r;
}

/**
 * @brief Création aléatoire de monstres dans la pièce entre 0 et 6
 *
 * @param r la pièce
 * @param monsterfile chemin du fichier *.mtbob
 */
void createMonsterList(Room *r, char *monsterfile)
{
    r->monsters = newMonsterList();
    MonsterList *monsterList = readMonsterFile(monsterfile);
    int numberOne = rand() % 7;
    int numberTwo = 0;
    if (numberOne < 6)
    {
        numberTwo = rand() % (7 - numberOne);
    }
    int index = rand() % monsterList->size;
    for (int i = 0; i < numberOne; i += 1)
    {
        addMonsterList(monsterList->list[index], r->monsters);
    }
    index = rand() % monsterList->size;
    for (int i = 0; i < numberTwo; i += 1)
    {
        addMonsterList(monsterList->list[index], r->monsters);
    }

    // 10% de chance d'être champion pour un monstre
    int random = rand() % 10;
    switch (random)
    {
    case 9:
        for (int i = 0; i < r->monsters->size; i += 1)
        {
            r->monsters->list[i]->hpMax *= 2;
            r->monsters->list[i]->dmg *= 2;
        }
        break;
    }
}

/**
 * @brief procédure qui dessine la pièce r selon le design
 *
 * @param r la pièce
 * @param design
 */
void createMapRoom(Room *r, int design)
{
    r->map = malloc(sizeof(char *) * r->rows);
    for (int i = 0; i < r->rows; i += 1)
    {
        r->map[i] = malloc(sizeof(char) * r->columns);
    }
    switch (design)
    {
    case 1:
        wallBorders(r); // construction des murs et portes de la pièce
        designRoom1(r); // construction de l'intérieur de la pièce
        break;
    case 2:
        wallBorders(r);
        designRoom2(r);
        break;
    case 3:
        wallBorders(r);
        designRoom3(r);
        break;
    case 4:
        wallBorders(r);
        designRoom4(r);
        break;
    case 5:
        wallBorders(r);
        designRoom5(r);
        break;
    case 6: // room de type 'Wall'
        designNoRoom(r);
        break;
    default:
        wallBorders(r); // pièce vide
        break;
    }
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

void designNoRoom(Room *r)
{
    for (int i = 0; i < r->rows; i += 1)
    {
        for (int j = 0; j < r->columns; j += 1)
        {
            if (i == j)
            {
                r->map[i][j] = ' ';
            }
            else
            {
                r->map[i][j] = 'W';
            }
        }
    }
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
                r->map[i][j] = 'W';
                /*
                if (j != r->columns / 2)
                {
                    r->map[i][j] = 'W';
                }
                else
                {
                    r->map[i][j] = 'D';
                }
                */
            }
            // ligne du milieu
            else if (i == r->rows / 2)
            {
                if (j == 0 || j == r->columns - 1)
                {
                    r->map[i][j] = 'W';
                    // r->map[i][j] = 'D';
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
void printRoom(Room room, FILE *f)
{
    fprintf(f, "[%d|%d]%d\n", room.rows, room.columns, room.id);
    for (int i = 0; i < room.rows; i += 1)
    {
        for (int j = 0; j < room.columns; j += 1)
        {
            fputc(room.map[i][j], f);
        }
        fputc('\n', f);
    }
}

void updateRoom(Room *room, char thing, int row, int column)
{
    room->map[row][column] = thing;
}

void freeRoom(Room *room)
{
    for (int i = 0; i < room->rows; i += 1)
    {
        free(room->map[i]);
    }
    free(room->map);
    freeItem(room->item);
    freeMonsterList(room->monsters);
    free(room->type);
    free(room);
}