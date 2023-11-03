/*
**  Filename : itemFile.c
**
**  Made by : HT
**
**  Description : editor of a item file *.itbob
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "itemFile.h"
#include "itemList.h"

/**
 * @brief crée et écris dans un fichier le contenu de la liste des items
 *
 * @param itemList objet complexe contenant la liste des items
 * @param itemfile chemin du fichier à créer de type *.itbob
 */
void writeItemFile(ItemList itemList, char *itemfile)
{
    FILE *f = fopen(itemfile, "w");
    if (f != NULL)
    {
        printItemList(itemList, f);
        fclose(f);
    }
    else
    {
        printf("Erreur à l'écriture: %s (writeItemFile)\n", itemfile);
    }
}

/**
 * @brief Create a Item object and add it in the end of itemfile
 * 
 * @param itemfile path of the file itbob
 */
void createItem(char *itemfile)
{
    Item *item;
    item = askItem(NULL);
    showItem(*item);
    addItemFile(item, itemfile);
    showItemList(*readItemFile(itemfile));
    freeItem(item);
}

/**
 * @brief ajout d'un item à la fin du fichier
 *
 * @param item un objet personnage
 * @param itemfile chemin du fichier à modifier de type *.itbob
 */
void addItemFile(Item *item, char *itemfile)
{
    FILE *f = fopen(itemfile, "r+");
    if (f != NULL)
    {
        int total;
        fscanf(f, "{%d}\n", &total); // par défaut lecture au début du fichier et écriture à la fin du fichier
        printItem(*item, f);
        fseek(f, 0, SEEK_SET);
        fprintf(f, "{%d}\n", total + 1);
        fclose(f);
    }
    else
    {
        printf("Erreur à l'ajout de l'item %s\n", item->name);
    }
}

void removeItemFile(Item *item, char *itemfile)
{
    FILE *f = fopen(itemfile, "r+");
    if (f != NULL)
    {
        ItemList *itemList = readItemFile(itemfile);
        removeItem(item, itemList);
        writeItemFile(*itemList, itemfile);
        freeItemList(itemList);
        fclose(f);
    }
}

// void removeItemFileByName(char *name, char *itemfile)
// {
//     FILE *f = fopen(itemfile, "r+");
//     if (f != NULL)
//     {
//         ItemList *itemList = readItemList(itemfile);
//         removeItemListByName(name, itemList);
//         writeItemFile(*itemList, itemfile);
//         freeItemList(itemList);
//         fclose(f);
//     }
// }

void removeItemByIndexFile(int index, char *itemfile)
{
    FILE *f = fopen(itemfile, "r+");
    if (f != NULL)
    {
        ItemList *itemList = readItemFile(itemfile);
        removeItemListByIndex(index, itemList);
        writeItemFile(*itemList, itemfile);
        freeItemList(itemList);
        fclose(f);
    }
}

ItemList *readItemFile(char *itemfile)
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

Item* randomItem(char* itemfile){
    ItemList* itemList = readItemFile(itemfile);
    Item* i = itemList->list[rand() % itemList->size];
    Item* item = newItem(i->name, i->hpMax, i->shield, i->dmg, i->ps, i->ss, i->flight);
  
    freeItemList(itemList);
    return item;
}