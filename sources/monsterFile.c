/*
**  Filename : monsterFile.c
**
**  Made by : HT
**
**  Description : editor of a file full of monsters *.mtbob
*/

#include <stdio.h>
#include "monsterFile.h"
#include "monsterList.h"
#include "monster.h"

void writeMonsterFile(MonsterList monsterList, char *monsterfile)
{
    FILE *f = fopen(monsterfile, "w");
    if (f != NULL)
    {
        printMonsterList(monsterList, f);
        fclose(f);
    }
    else
    {
        printf("Erreur à l'écriture du fichier %s\n", monsterfile);
    }
}

MonsterList* readMonsterFile(char *monsterfile)
{
    FILE *f = fopen(monsterfile, "r");
    if (f != NULL)
    {
        MonsterList* monsterList = newMonsterList();
        fscanf(f, "{%d}\n", &monsterList->size);
        for (int i = 0; i < monsterList->size; i += 1)
        {
            monsterList->list[i] = readMonster(f);
            printf("name---: %s\n", monsterList->list[i]->name);
        }
        fclose(f);
        return monsterList;
    }
    else
    {
        printf("readMonsterFile(): Erreur à la lecture du fichier %s\n", monsterfile);
        return NULL;
    }
}

int addMonsterFile(Monster *monster, char *monsterfile)
{
    FILE *f = fopen(monsterfile, "r+");
    if (f != NULL)
    {
        int monsterTotal = 0;
        fscanf(f, "{%d}\n", &monsterTotal);
        printMonster(*monster, f);
        fseek(f, 0, SEEK_SET);
        fprintf(f, "{%d}\n", monsterTotal + 1);
        fclose(f);
        return 1;
    }
    else
    {
        printf("Erreur à l'ajout d'un monstre dans le fichier : %s\n", monsterfile);
        return 0;
    }
}

/**
 * @brief Create a Monster object and add it in the end of monsterfile
 * 
 * @param monsterfile path of the file mtbob
 */
void createMonster(char* monsterfile)
{
    Monster *monster;
    monster = askMonster(NULL);
    showMonster(*monster);
    addMonsterFile(monster, monsterfile);
    MonsterList* monsterList = readMonsterFile(monsterfile);
    showMonsterList(*monsterList);
    freeMonsterList(monsterList);
    //freeMonster(monster);
}