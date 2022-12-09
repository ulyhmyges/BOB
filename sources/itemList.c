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

ItemList *readItemList(char *itemfile)
{
    FILE *f = fopen(itemfile, "r");
    if (f != NULL)
    {
        ItemList *itemList = newItemList();
        fscanf(f, "{%d}\n", &itemList->size);
        for (int i = 0; i < itemList->size; i += 1)
        {
            itemList->list[i] = readItem(f);
        }
        fclose(f);
        return itemList;
    }
    else
    {
        printf("Erreur à la lecture du fichier %s\n", itemfile);
        return NULL;
    }
}

/**
 * @brief supprime la première occurrence item de la liste et retourne 1 en cas de succès et 0 sinon
 *
 * @param item élément à supprimer
 * @param itemList objet contenant la liste des objets personnage
 * @return int
 */
int removeItemList(Item *item, ItemList *itemList)
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

/**
 * @brief supprime un item de la liste selon l'attribut name
 *
 * @param name attribut d'un item
 * @param itemList objet complexe contenant la liste des items
 * @return int
 */
int removeItemListByName(char *name, ItemList *itemList)
{
    int i;
    for (i = 0; i < itemList->size; i += 1)
    {
        if (!strcmp(itemList->list[i]->name, name))
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
