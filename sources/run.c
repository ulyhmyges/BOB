/*
**  Filename : run.c
**
**  Made by : HT
**
**  Description : attempt to start the bob's game
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "player.h"
#include "playerFile.h"
#include "itemFile.h"
#include "item.h"
#include "monsterFile.h"
#include "lowercase.h"

Player* selectPlayer(char *playerfile)
{
    puts("Welcome at Bob's game");
    puts("Choose your player:");
    puts("-> Briatte");
    puts("-> Chevaillier");
    puts("-> Hennou");
    char *name = malloc(sizeof(char) * 12);
    do
    {
        printf("Tape the name of your player: ");
        scanf("%s", name);
        lowercase(name);
    } while (strcmp(name, "briatte") && strcmp(name, "chevaillier") && strcmp(name, "hennou"));
    puts("start...");
    Player *player;
    PlayerList *playerList = readPlayerFile(playerfile);
    switch (name[0])
    {
    case 'b':
        player = newPlayer("Briatte", 3, 0, 3.50, false, false, false, 1);
        break;
    case 'c':
        player = newPlayer("Chevaillier", 1, 8, 2.50, false, false, true, 1);
        break;

    case 'h':
        player = newPlayer("Hennou", 6, 0, 2, false, false, false, 1);
        break;
    }
    for (int i = 0; i < playerList->size; i += 1)
    {
        if (!strcmp(playerList->list[i]->name, player->name))
        {
            player = playerList->list[i];
        }
    }
    return player;
}

/**
 * @brief CLI CRUD des items
 *
 */
void crudItem()
{
    puts("CRUD FOR ITEMS");
    char *input = malloc(sizeof(char) * 7);
    char *itemfile = malloc(sizeof(char) * 77);
    puts("Which file do you want to use?");
    printf("Enter the path for item file (itbob): ");
    scanf("%s", itemfile);
    FILE *f = fopen(itemfile, "r+");
    if (f == NULL)
    {
        printf("File error: '%s'!\n", itemfile);
        exit(1);
    }
    fclose(f);
    do
    {
        puts("Choose a option:");
        puts("-> Show");
        puts("-> Add");
        puts("-> Update");
        puts("-> Remove");
        scanf("%s", input);
        lowercase(input);
    } while (strcmp(input, "show") && strcmp(input, "add") && strcmp(input, "update") && strcmp(input, "remove"));

    ItemList *itemList = readItemFile(itemfile);
    switch (input[0])
    {
    case 's': // Show all items from itemfile
        showItemList(*itemList);
        break;

    case 'a': // Add an item
        createItem(itemfile);
        break;

    case 'u': // Update an item
        if (updateItemByName(itemList))
        {
            writeItemFile(*itemList, itemfile);
        }
        break;

    case 'r': // Remove an item
        if (removeItemByName(itemList))
        {
            writeItemFile(*itemList, itemfile);
        }
        break;
    }
    freeItemList(itemList);
    free(input);
    free(itemfile);
}

/**
 * @brief CLI CRUD of monsters
 * 
 */
void crudMonster()
{
    puts("CRUD FOR MONSTERS");
    char* input = malloc(sizeof(char) * 7);
    char* monsterfile = malloc(sizeof(char) * 77);
    puts("Which file do you want to use?");
    printf("Enter the path for monster file (mtbob): ");
    scanf("%s", monsterfile);
    // FILE *f = fopen(monsterfile, "r+");
    // if (f == NULL)
    // {
    //     printf("File error: '%s'!\n", monsterfile);
    //     exit(1);
    // }
    // fclose(f);
    do
    {
        puts("Choose a option:");
        puts("-> Show");
        puts("-> Add");
        puts("-> Update");
        puts("-> Remove");
        scanf("%s", input);
        lowercase(input);
    } while (strcmp(input, "show") && strcmp(input, "add") && strcmp(input, "update") && strcmp(input, "remove"));

    MonsterList* monsterList = readMonsterFile(monsterfile);
    printf("length: %d\n", monsterList->size);
    printf("path: %s\n", monsterfile);
    switch (input[0])
    {
    case 's': // Show all monsters from monsterList
        showMonsterList(*monsterList);
        break;

    case 'a': // Add an monster
        createMonster(monsterfile);
        break;

    case 'u': // Update an monster
        if (updateMonsterByName(monsterList))
        {
            writeMonsterFile(*monsterList, monsterfile);
        }
        break;

    case 'r': // Remove an monster
        if (removeMonsterByName(monsterList))
        {
            writeMonsterFile(*monsterList, monsterfile);
        }
        break;
    }
    freeMonsterList(monsterList);
    free(input);
    free(monsterfile);
}