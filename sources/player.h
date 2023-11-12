/*
**  Filename : player.h
**
**  Made by : HT
**
**  Description : model of a player (Briatte, Chevaillier or Hennou)
**
** Briatte 3 hpMax | 3.50 dmg
** Chevaillier 1 hpMax | 2.5 dmg | 8 shield | flight 
** Hennou 6 hpMax | 2 dmg
*/


#ifndef PLAYER_H

#define PLAYER_H
#include "item.h"
#include "itemList.h"

typedef enum Health {
    dead,
    inShape,
    inPain
} Health;

typedef struct Player
{
    char *name;
    float hpMax;    //3 pour Briatte
    float hp;
    int shield;
    float dmg;      //3.50 pour Briatte
    boolean ps;
    boolean ss;
    boolean flight;
    int achieve;        // niveau à réussir: 1, 2 ou 3
    boolean invincible; // true par défaut
    ItemList* itemList; // vide par défaut
    Health state;
    char* pathPlayerfile;
    boolean chevaillier;
    boolean hennou;
    boolean unlock;
} Player;

Player *newPlayer(char *name, float hpMax, int shield, float dmg, boolean ps, boolean ss, boolean flight, int achieve);
void freePlayer(Player *player);
Player * readPlayer(FILE *f);
void writePlayer(Player player, FILE *f);
void showPlayer(Player player);
void statsPlayer(Player* player);

void upgradePlayer(Player* player, Item* item);
float ouch(Player* player, float dmg);

#endif // PLAYER_H