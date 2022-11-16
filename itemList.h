#ifndef ITEMLIST_H

#define ITEMLIST_H
#include "item.h"

typedef struct ItemList {
    Item **list;
    int size;
    int capacity;
} ItemList;

ItemList * newItemList(void);
void freeItemList();
void printItemList(ItemList itemList, FILE *f);
void showItemList(ItemList itemList);
int addItemList(Item *item, ItemList *itemList);
int removeItemList(Item *item, ItemList *itemList);
int removeItemListByName(char *name, ItemList *itemList);
int removeItemListByIndex(int index, ItemList *itemList);
ItemList * readItemList(char *fwd);

#endif