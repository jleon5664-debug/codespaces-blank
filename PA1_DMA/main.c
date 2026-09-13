/* COP 3502C PA1 This program is written by: Jeronimo Leon */

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// constraints, +1 for \0
#define MAX_STR_LEN 51  
#define MAX_POPULATION 1000000
// data structures
    typedef struct monster
    {
        char *name;
        char *element;
        int population;

    } monster;

    typedef struct region
    {
        char *name;
        int monster_cnt;
        int total_population;
        monster **monsters;
    } region;

    typedef struct itinerary
    {
        int region_cnt;
        region **regions;
        int captures;
    } itinerary;

    typedef struct trainer
    {
        char *name;
        itinerary *visits;
    } trainer;

// declare prototypes
    char* readAndAllocateString(void);

    monster* makeMonster(char *name, char *element, int population);

    monster** readMonsters(int *monsterCount);

    region** readRegions(int *countRegions, monster** monsterList, int monsterCount);

    trainer* loadTrainers(int *trainerCount, region** regionList, int countRegions);

    void processInputs(monster** monsterList, int monsterCount, region** regionList, 
        int regionCount, trainer* trainerList, int trainerCount);
    
    void releaseMemory(monster** monsterList, int monsterCount, region** regionList,
        int regionCount, trainer* trainerList, int trainerCount);

// driver
int main(void) {

    // tracking variables
    int monsterCount = 0;
    int regionCount = 0;
    int trainerCount = 0;

    // master pointer to hold DMA
    monster** masterMonsterList = NULL;
    region** masterRegionList = NULL;
    trainer* masterTrainerList = NULL;

    // push data load sequence
    masterMonsterList = readMonsters(&monsterCount);
    masterRegionList = readRegions(&regionCount, masterMonsterList, monsterCount);
    masterTrainerList = loadTrainers(&trainerCount, masterRegionList, regionCount);

    // process math & print outputs
    processInputs(masterMonsterList, monsterCount, masterRegionList, regionCount, masterTrainerList, trainerCount);

    // release allocated memory
    releaseMemory(masterMonsterList, monsterCount, masterRegionList, regionCount, masterTrainerList, trainerCount);

    return 0;
}

// function definitions

char* readAndAllocateString(void) {
    // declare char limit
    char name[MAX_STR_LEN];

    // read string inputs into name
    scanf("%50s", name);

    // measure string length +1 for \0
    int length = strlen(name) + 1;
    
    // DMA on the heap
    char* length = (char*)malloc(length * sizeof(char));

    // copy string from stack into heap mem
    strcpy(length, name);

    // return p
    return length;
}