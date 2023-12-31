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

Run *newRun(char *playerfile, char *roomfile, char *itemfile, char *monsterfile)
{
    Run *run = malloc(sizeof(Run));
    run->ptbob = malloc(sizeof(char) * 99);
    run->rtbob = malloc(sizeof(char) * 99);
    run->itbob = malloc(sizeof(char) * 99);
    run->mtbob = malloc(sizeof(char) * 99);
    strcpy(run->ptbob, playerfile);
    strcpy(run->rtbob, roomfile);
    strcpy(run->itbob, itemfile);
    strcpy(run->mtbob, monsterfile);
    return run;
}

void freeRun(Run *run)
{
    free(run->ptbob);
    free(run->rtbob);
    free(run->itbob);
    free(run->mtbob);
    free(run);
}

void game(Level *level)
{
    char c;
    while (1)
    {
        showCurrentRoom(level);
        statsPlayer(level->player);
        if (isType(level, level->coord.u, level->coord.v, "Boss") && level->currentRoom->monsters->list[0]->hpMax > 10)
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
        level->player->invincible = true;
        level = newLevel(level->id + 1, level->rows, level->columns, level->pathRoomfile, level->pathItemfile, level->pathMonsterfile, level->player);
        showCurrentRoom(level);
    }
    // end of the game
    if (isEnd(level, level->coord.p.h, level->coord.p.w))
    {
        // level achieved, 3 levels max
        if (level->player->achieve < 3)
        {
            level->player->achieve += 1;
        }

        showEnd();

        // save the game
        savePlayer(level->player);
        exit(0);
    }
    return level;
}

void start()
{
    // clear screen
    printf("\e[1;1H\e[2J");

    // color of the sceen
    system("echo '\e[032m'");

    for (int i = 0; i < 15; i += 1)
    {
        printf("\n");
    }
    puts("Welcome at Bob's game");

    puts("Choose one option (p, r, i or m):");

    // display players from the playerfile
    printf("Play\n");
    printf("Room's CRUD\n");
    printf("Item's CRUD\n");
    printf("Monster's CRUD\n");

    char *option = malloc(sizeof(char) * 12);
    do
    {
        printf("Which option?: ");
        scanf("%s", option);
        lowercase(option);
    } while (strcmp(option, "p") && strcmp(option, "r") && strcmp(option, "i") && strcmp(option, "m"));

    switch (option[0])
    {
    case 'p':
        newGame();
        break;

    case 'r':
        break;

    case 'i':
        crudItem();
        break;

    case 'm':
        crudMonster();
        break;

    default:
        newGame();
    }
}