/*
**  Filename : itemFile.h
**
**  Made by : HT
**
**  Description : editor of a item file *.itbob
*/

#ifndef ITEMFILE_H

#define ITEMFILE_H
#include "itemList.h"

void writeItemFile(ItemList itemList, char *itemfile);
void addItemFile(Item *item, char *itemfile);
void removeItemFile(Item *item, char *itemfile);
void removeItemFileByName(char *name, char *itemfile);
void removeItemFileByIndex(int index, char *itemfile);
ItemList * readItemFile(char *itemfile);


#endif // ITEMFILE_H