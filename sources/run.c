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
#include "run.h"

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
 * @brief CRUD of monsters
 *
 */
void crudMonster()
{
    puts("CRUD FOR MONSTERS");
    char *input = malloc(sizeof(char) * 7);
    char *monsterfile = malloc(sizeof(char) * 77);
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

    MonsterList *monsterList = readMonsterFile(monsterfile);
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

void newGame()
{

    char *playerfile = malloc(sizeof(char) * 99);
    strcpy(playerfile, "/Users/ulyh/programmation/c/bbriatte/bob/binding_of_briatte/ressources/file.ptbob");

    // à modifier
    Player *player = selectPlayer(playerfile);

    // niveau 1: id=1
    char *roomfile = malloc(sizeof(char) * 99);
    strcpy(roomfile, "/Users/ulyh/programmation/c/bbriatte/bob/binding_of_briatte/ressources/file.rtbob");

    char *itemfile = malloc(sizeof(char) * 99);
    strcpy(itemfile, "/Users/ulyh/programmation/c/bbriatte/bob/binding_of_briatte/ressources/file.itbob");

    char *monsterfile = malloc(sizeof(char) * 99);
    strcpy(monsterfile, "/Users/ulyh/programmation/c/bbriatte/bob/binding_of_briatte/ressources/file.mtbob");

    Level *level = newLevel(1, 9, 15, roomfile, itemfile, monsterfile, player);

    game(level);
}

void game(Level *level)
{
    char c;
    while (1)
    {
        showCurrentRoom(level);
        statsPlayer(level->player);
        if (isType(level, level->coord.u, level->coord.v, "Boss") && level->currentRoom->monsters->list[0]->hpMax > 5)
        {
            printf("=======monster hp: %.2f =======================", level->currentRoom->monsters->list[0]->hpMax);
            printf("=======monster name: %s==========================", level->currentRoom->monsters->list[0]->name);
        }

        while (!kbhit())
        {
        }
        c = getchar();

        // player can shoot with o

        if (canShoot(level))
        {
            shoot(level, c);
        }
        movePerson(level, c);
        level = endOrNextLevel(level);

        fflush(stdin);
        //  sleep(3);
    }
}

Level *endOrNextLevel(Level *level)
{
    // next level
    if (isNext(level, level->coord.p.h, level->coord.p.w))
    {
        // go to next level
        level = newLevel(level->id + 1, level->rows, level->columns, level->pathRoomfile, level->pathItemfile, level->pathMonsterfile, level->player);
        showCurrentRoom(level);
    }
    // end of the game
    if (isEnd(level, level->coord.p.h, level->coord.p.w))
    {
        level->player->achieve += 1;
        showEnd();
        // save the game
        savePlayer(level->player);
        exit(0);
    }
    return level;
}
