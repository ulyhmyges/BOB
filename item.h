#ifndef ITEM_H

#define ITEM_H

typedef enum boolean {
    false,
    true
} boolean;

typedef struct Item {
    char *name;
    int hpMax;
    int shield;
    int dmg;
    enum boolean ps;         //bouléen true=1 ou false=0
    enum boolean ss;         //bouléen
    enum boolean flight;     //bouléen
} Item;



Item * newItem(char *name, int hpMax, int shield, int dmg, boolean ps, boolean ss, boolean flight);
void freeItem(Item *item);
void showItem(Item item);
void printItem(Item item, FILE *f);
#endif