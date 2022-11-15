#ifndef ITEMFILE_H

#define ITEMFILE_H
#include "itemList.h"

void writeItemFile(ItemList itemList, char *fwd);
void addItemFile(Item item, char *fwd);
ItemList * readItemList(char *fwd);
Item * readItem(FILE *f);

#endif // ITEMFILE_H