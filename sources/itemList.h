/*
**  Filename : itemList.h
**
**  Made by : HT
**
**  Description : list of items' pointers
*/

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
int removeItem(Item *item, ItemList *itemList);
int removeItemByName(ItemList *itemList);
int removeItemListByIndex(int index, ItemList *itemList);
ItemList* readItemList(char *itemfile);
Item* getItemByName(ItemList *itemList);
int updateItemByName(ItemList* itemList);

#endif