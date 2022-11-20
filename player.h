#ifndef PLAYER_H

#define PLAYER_H
#include "item.h"

typedef struct Player
{
    char *name;
    float hpMax;    //3 pour Briatte
    int shield;
    float dmg;      //3.50 pour Briatte
    boolean ps;
    boolean ss;
    boolean flight;
    int achieve;        // niveau à réussir: 1, 2 ou 3
    boolean invincible; // true par défaut
    Item *item; // aucun par défaut
} Player;

Player *newPlayer(char *name, float hpMax, int shield, float dmg, boolean ps, boolean ss, boolean flight, int achieve);
void freePlayer(Player *player);
Player * readPlayer(FILE *f);
void printPlayer(Player player, FILE *f);
void showPlayer(Player player);

#endif // PLAYER_H