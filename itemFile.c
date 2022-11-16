#include <stdio.h>
#include <string.h>
#include "itemFile.h"
#include "itemList.h"

/**
 * @brief crée et écris dans un fichier le contenu de la liste des items
 *
 * @param itemList objet complexe contenant la liste des items
 * @param fwd chemin du fichier à créer de type *.itbob
 */
void writeItemFile(ItemList itemList, char *fwd)
{
    FILE *f = fopen(fwd, "w");
    if (f != NULL)
    {
        printItemList(itemList, f);
        fclose(f);
    }
    else
    {
        printf("Erreur à l'écriture: %s (writeItemFile)\n", fwd);
    }
}

/**
 * @brief ajout d'un item à la fin du fichier
 *
 * @param item un objet personnage
 * @param fwd chemin du fichier à modifier de type *.itbob
 */
void addItemFile(Item *item, char *fwd)
{
    FILE *f = fopen(fwd, "r+");
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

void removeItemFile(Item *item, char *fwd)
{
    FILE *f = fopen(fwd, "r+");
    if (f != NULL)
    {
        ItemList *itemList = readItemList(fwd);
        removeItemList(item, itemList);
        writeItemFile(*itemList, fwd);
        freeItemList(itemList);
        fclose(f);
    }
}

void removeItemFileByName(char *name, char *fwd)
{
    FILE *f = fopen(fwd, "r+");
    if (f != NULL)
    {
        ItemList *itemList = readItemList(fwd);
        removeItemListByName(name, itemList);
        writeItemFile(*itemList, fwd);
        freeItemList(itemList);
        fclose(f);
    }
}

void removeItemFileByIndex(int index, char *fwd)
{
    FILE *f = fopen(fwd, "r+");
    if (f != NULL)
    {
        ItemList *itemList = readItemList(fwd);
        removeItemListByIndex(index, itemList);
        writeItemFile(*itemList, fwd);
        freeItemList(itemList);
        fclose(f);
    }
}

ItemList *readItemFile(char *fwd)
{
    FILE *f = fopen(fwd, "r");
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
        printf("Erreur à la lecture du fichier %s\n", fwd);
        return NULL;
    }
}