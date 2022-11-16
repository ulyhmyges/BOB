#include <stdio.h>
#include "monsterFile.h"
#include "monsterList.h"
#include "monster.h"

void writeMonsterFile(MonsterList monsterList, char *fwd)
{
    FILE *f = fopen(fwd, "w");
    if (f != NULL)
    {
        printMonsterList(monsterList, f);
        fclose(f);
    }
    else
    {
        printf("Erreur à l'écriture du fichier %s\n", fwd);
    }
}

MonsterList *readMonsterFile(char *fwd)
{
    FILE *f = fopen(fwd, "r");
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
        printf("Erreur à la lecture du fichier %s\n", fwd);
        return NULL;
    }
}

int addMonsterFile(Monster *monster, char *fwd)
{
    FILE *f = fopen(fwd, "r+");
    if (f != NULL)
    {
        MonsterList *monsterList = newMonsterList();
        fscanf(f, "{%d}\n", &monsterList->size);
        printMonster(*monster, f);
        monsterList->size += 1;
        fseek(f, 0, SEEK_SET);
        fprintf(f, "{%d}\n", monsterList->size);
        fclose(f);
        return 1;
    }
    else
    {
        printf("Erreur à l'ajout d'un monstre dans le fichier : %s\n", fwd);
        return 0;
    }
}
int removeMonsterFile(Monster *monster, char *fwd);
int removeMonsterFileByName(char *name, char *fwd);
int removeMonsterFileByIndex(int index, char *fwd);