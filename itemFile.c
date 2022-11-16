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
void addItemFile(Item item, char *fwd)
{
    FILE *f = fopen(fwd, "r+");
    if (f != NULL)
    {
        int total;
        fscanf(f, "{%d}\n", &total); // par défaut lecture au début du fichier et écriture à la fin du fichier
        printItem(item, f);
        fseek(f, 0, SEEK_SET);
        fprintf(f, "{%d}\n", total + 1);
        fclose(f);
    }
    else
    {
        printf("Erreur à l'ajout de l'item %s\n", item.name);
    }
}

void removeItemFile(Item *item, char *fwd)
{
    FILE *f = fopen(fwd, "r+");
    if (f != NULL)
    {
        ItemList *itemList = readItemList(fwd);
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

        if (index >= 0 && index < itemList->size)
        {
            freeItem(itemList->list[index]);
            itemList->size -= 1;
        }

        for (int j = index; j < itemList->size; j += 1)
        {
            itemList->list[j] = itemList->list[j + 1];
        }
        writeItemFile(*itemList, fwd);
        freeItemList(itemList);
        fclose(f);
    }
}

ItemList *readItemList(char *fwd)
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

Item *readItem(FILE *f)
{
    Item *item = newItem("a", 0, 0, 0, false, false, false);
    char binaire[5];
    char var[50];
    fgets(var, 50, f);
    if (!strcmp(var, "---\n"))
    {
        fgets(var, 30, f);
    }
    sscanf(var, "name=%[^\n]", item->name);
    fgets(var, 30, f);
    int i = sscanf(var, "hpMax=%d\n", &item->hpMax); // succès = 1 et échec = 0
    if (i == 1)
    {
        fgets(var, 30, f);
    }
    i = sscanf(var, "shield=%d\n", &item->shield);
    if (i == 1)
    {
        fgets(var, 30, f);
    }
    i = sscanf(var, "dmg=%f\n", &item->dmg);
    if (i == 1)
    {

        fgets(var, 30, f);
    }
    i = sscanf(var, "ps=%s\n", binaire);
    if (i == 1)
    {
        item->ps = true;
        fgets(var, 30, f);
    }
    i = sscanf(var, "ss=%s\n", binaire);
    if (i == 1)
    {
        item->ss = true;
        fgets(var, 30, f);
    }
    i = sscanf(var, "flight=%s\n", binaire);
    if (i == 1)
    {
        item->flight = true;
        fgets(var, 30, f);
    }
    fseek(f, -4, SEEK_CUR);
    return item;
}