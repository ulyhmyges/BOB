/*
**  Filename : itemList.c
**
**  Made by : HT
**
**  Description : list of items' pointers
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "itemList.h"
#include "item.h"
#include "itemFile.h"

ItemList *newItemList(void)
{
    ItemList *itemList = malloc(sizeof(ItemList));
    itemList->capacity = 35;
    itemList->size = 0;
    itemList->list = malloc(sizeof(Item *) * itemList->capacity);
    return itemList;
}

void freeItemList(ItemList *itemList)
{
    for (int i = 0; i < itemList->size; i += 1)
    {
        freeItem(itemList->list[i]);
    }
    free(itemList->list);
    free(itemList);
}
/**
 * @brief écrit le contenu de la liste des items dans le fichier correspondant au pointeur f
 *
 * @param itemList objet complexe contenant la liste des items
 * @param f pointeur f d'un fichier à l'état d'écriture
 */
void printItemList(ItemList itemList, FILE *f)
{
    fprintf(f, "{%d}\n", itemList.size);
    for (int i = 0; i < itemList.size; i += 1)
    {
        printItem(*itemList.list[i], f);
    }
}

void showItemList(ItemList itemList)
{
    printf("{%d}\n", itemList.size);
    for (int i = 0; i < itemList.size; i += 1)
    {
        showItem(*itemList.list[i]);
    }
}

/**
 * @brief ajoute un item à la liste et retourne 1 en cas de succès et 0 sinon
 *
 * @param item un objet personnage
 * @param itemList objet complexe contenant la liste des items
 * @return int
 */
int addItemList(Item *item, ItemList *itemList)
{
    if (itemList->size < itemList->capacity)
    {
        itemList->list[itemList->size] = item;
        itemList->size += 1;
        return 1;
    }
    else
    {
        // modifier la capacité du tableau !!
        return 0;
    }
}

/**
 * @brief Get the Item By Name from itemList
 *
 * @param name
 * @param itemList Liste d'items
 * @return Item*
 */
Item* getItemByName(ItemList *itemList)
{
    char *name = malloc(sizeof(char) * 35);
    puts("Name of the item?:"); 
    
    // Pourquoi erreur de lecture ?
    if (fgets(name, 34, stdin) != NULL) {
        printf("");
    };
      if (fgets(name, 34, stdin) != NULL) {
        printf("Error reading input");
    };
    sscanf(name, "%[^\n]", name);
    int i;
    for (i = 0; i < itemList->size; i += 1)
    {
        if (!strcmp(itemList->list[i]->name, name))
        {
            return itemList->list[i];
        }
    }
    free(name);
    return NULL;
}

int updateItemByName(ItemList *itemList)
{
    Item* item;
    item = getItemByName(itemList);
    if (item == NULL)
    {
        printf("Item not found\n");
        return 0;
    }
    showItem(*item);
    item = askItem(item);
    showItem(*item);
    //freeItem(item);
    return 1;
}

/**
 * @brief Remove item by name from itemList
 *
 * @param itemList Object complexe contenant la liste des items
 * @return 1 if succeed 0 otherwise
 */
int removeItemByName(ItemList *itemList)
{
    Item *item;
    item = getItemByName(itemList);
    if (item == NULL)
    {
        printf("Item not found\n");
        return 0;
    }
    showItem(*item);
    removeItem(item, itemList);
    printf("Item %s removed.\n", item->name);
    freeItem(item);
    return 1;
}

/**
 * @brief supprime la première occurrence item de la liste et retourne 1 en cas de succès et 0 sinon
 *
 * @param item élément à supprimer
 * @param itemList objet contenant la liste des objets personnage
 * @return int
 */
int removeItem(Item *item, ItemList *itemList)
{
    int i;
    for (i = 0; i < itemList->size; i += 1)
    {
        if (itemList->list[i] == item)
        {
            freeItem(itemList->list[i]);
            itemList->size -= 1;
            break;
        }
    }
    for (int j = i; j < itemList->size; j += 1)
    {
        itemList->list[j] = itemList->list[j + 1];
    }
    if (i <= itemList->size)
    {
        return 1;
    }
    return 0;
}

int removeItemListByIndex(int index, ItemList *itemList)
{
    if (index >= 0 && index < itemList->size)
    {
        freeItem(itemList->list[index]);
        itemList->size -= 1;
        for (int j = index; j < itemList->size; j += 1)
        {
            itemList->list[j] = itemList->list[j + 1];
        }
        return 1;
    }
    return 0;
}
