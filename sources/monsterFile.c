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

MonsterList *readMonsterFile(char *monsterfile)
{
    FILE *f = fopen(monsterfile, "r");
    if (f != NULL)
    {
        MonsterList *monsterList = newMonsterList();
        fscanf(f, "{%d}\n", &monsterList->size);
        for (int i = 0; i < monsterList->size; i += 1)
        {
            monsterList->list[i] = readMonster(f);
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
void removeMonsterFile(Monster *monster, char *monsterfile);
void removeMonsterFileByName(char *name, char *monsterfile);
void removeMonsterFileByIndex(int index, char *monsterfile);