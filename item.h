#ifndef ITEM_H

#define ITEM_H

typedef enum boolean {
    false,
    true
} boolean;

typedef struct Item {
    char *name;
    float hpMax;
    int shield;
    float dmg;
    boolean ps;         //bouléen true=1 ou false=0
    boolean ss;         //bouléen
    boolean flight;     //bouléen
} Item;



Item * newItem(char *name, float hpMax, int shield, float dmg, boolean ps, boolean ss, boolean flight);
void freeItem(Item *item);
void showItem(Item item);
void printItem(Item item, FILE *f);
Item * readItem(FILE *f);
#endif