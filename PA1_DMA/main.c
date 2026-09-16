/* COP 3502C PA1 This program is written by: Jeronimo Leon */

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// constraints, +1 for \0
#define MAX_STR_LEN 50  
#define STR(x) #x
#define XSTR(x) STR(x)
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

trainer* LoadTrainers(int *trainerCount, region** regionList, int countRegions);

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
    masterTrainerList = LoadTrainers(&trainerCount, masterRegionList, regionCount);

    // process math & print outputs
    processInputs(masterMonsterList, monsterCount, masterRegionList, regionCount, masterTrainerList, trainerCount);

    // release allocated memory
    releaseMemory(masterMonsterList, monsterCount, masterRegionList, regionCount, masterTrainerList, trainerCount);

    return 0;
}

// function definitions

char* readAndAllocateString(void) {
    // declare char limit
    char buffer_name[MAX_STR_LEN + 1];

    // read string inputs into name
    scanf("%50s", buffer_name);

    // measure string length +1 for \0
    int length = strlen(buffer_name) + 1;
    
    // DMA on the heap
    char *str = malloc(length * sizeof(char));

    // copy string from stack into heap mem
    strcpy(str, buffer_name);

    // return p
    return str;
}

monster* makeMonster(char *name, char *element, int population) {
    // allocate monster struct to heap
    monster *m = malloc(sizeof(monster));

    // copy & assignm value to struct members
    m->name = malloc(strlen(name) + 1);
    strcpy(m->name, name);
    m->element = malloc(strlen(element) + 1);
    strcpy(m->element, element);
    m->population = population;
    
    return m;
}

monster** readMonsters(int *monsterCount) {
    // read total # of monster from input
    scanf("%i", monsterCount);

    // allocate array of monster*
    monster **monsterList = malloc((*monsterCount) * sizeof(monster*)); 

    
       
    char name_buf[MAX_STR_LEN + 1];
    char element_buf[MAX_STR_LEN + 1];
    // int for pop
    int pop;


    for (int i = 0; i < *monsterCount; i++) {
        scanf("%50s", name_buf);
        scanf("%50s", element_buf);
        scanf("%i", &pop);

        monsterList[i] = makeMonster(name_buf, element_buf, pop);
    }

    return monsterList;
}

region** readRegions(int *countRegions, monster** monsterList, int monsterCount) {
    // read region count to update main() tracking
    scanf("%i", countRegions);

    // allocate region pointers into list
    region **regionList = malloc((*countRegions) * sizeof(region*));

    // loop for 
    for (int i = 0; i < *countRegions; i++) {
        //allocate to region struct
        regionList[i] = malloc(sizeof(region));

        // read region w allocate str
        regionList[i]->name = readAndAllocateString();
        
        scanf("%i", &(regionList[i]->monster_cnt));

        regionList[i]->monsters = malloc(regionList[i]->monster_cnt * sizeof(monster*));

        regionList[i]->total_population = 0;

        // read each m name and link to list
        for (int j = 0; j < regionList[i]->monster_cnt; j++) {
            char *temp_name = readAndAllocateString();

            // search list for match
            for (int k = 0; k < monsterCount; k++) {
                if (strcmp(temp_name, monsterList[k]->name) == 0) {
                // copy address of match
                regionList[i]->monsters[j] = monsterList[k];
                // sum total pop on mem
                regionList[i]->total_population += monsterList[k]->population;
                
                break;
                }
            }
            // free str mem
            free(temp_name);
        }
    }
        return regionList;
}

trainer* LoadTrainers(int *trainerCount, region** regionList, int countRegions) {
    // read trainer count to update main()
    scanf("%i", trainerCount);
    
    // allocate array if trainer struct
    trainer *trainerList = malloc((*trainerCount) * sizeof(trainer));

    for (int i = 0; i < *trainerCount; i++) {
        // read trainer 
        trainerList[i].name = readAndAllocateString();

        // allocate struct itinerary to heap
        trainerList[i].visits = malloc(sizeof(itinerary));
        
        // read capture and region count
        scanf("%i", &(trainerList[i].visits->captures));
        scanf("%i", &(trainerList[i].visits->region_cnt));

        // allocate 
        trainerList[i].visits->regions = malloc(trainerList[i].visits->region_cnt * sizeof(region*));

        // search list & link pointers
        for (int j = 0; j < trainerList[i].visits->region_cnt; j++) {
            char *temp_region = readAndAllocateString();

            for (int k = 0; k < countRegions; k++) {
                if (strcmp(temp_region, regionList[k]->name) == 0) {
                    // link mem address of region
                    trainerList[i].visits->regions[j] = regionList[k];

                    break;
                }
            }
            free(temp_region);
        }
    }
    return trainerList;
}

void processInputs(monster** monsterList, int monsterCount, region** regionList, int regionCount, trainer* trainerList, int trainerCount) {
    
    // silience warnings 
    (void)monsterList;
    (void)monsterCount;
    (void)regionList;
    (void)regionCount;
    
    // traverse trainer
    for (int i = 0; i < trainerCount; i++) {
        printf("%s\n", trainerList[i].name);

        // traverse trainer region
        for (int j = 0; j < trainerList[i].visits->region_cnt; j++) {
            
            // temporary pointer for readability
            region *currentRegion = trainerList[i].visits->regions[j];
            printf("%s\n", currentRegion->name);

            // traverse region monsters
            for (int k = 0; k < currentRegion->monster_cnt; k++) {
                
                monster *currentMonster = currentRegion->monsters[k];

                // double to prevent truncate to 0
                double rel_pop = (double)currentMonster->population;
                double total_pop = (double)currentRegion->total_population;
                double total_captures = (double)trainerList[i].visits->captures;

                // Calculate & round
                double expected = (rel_pop / total_pop) * total_captures;
                int final_captures = (int)round(expected);

                //  output filter
                if (final_captures > 0) {
                    printf("%d-%s\n", final_captures, currentMonster->name);
                }
            }
        }
        
        // print a blank line between trainers, stop before last one
        if (i < trainerCount - 1) {
            printf("\n");
        }
    }
}

void releaseMemory(monster** monsterList, int monsterCount, region** regionList, 
    int regioCount, trainer* trainerList, int trainerCount) {

        // teadrdown trainers
        for (int i = 0; i < trainerCount; i++) {
            free(trainerList[i].name);

            // free pointers within itinerary
            free(trainerList[i].visits->regions);

            // free struct 
            free(trainerList[i].visits);
        }
        free(trainerList);

        // teardown regions
        for (int i = 0; i < regioCount; i++) {
            free(regionList[i]->name);

            free(regionList[i]->monsters);

            free(regionList[i]);
        }
        free(regionList);

        // teardown monsters
        for (int i = 0; i < monsterCount; i++) {
            free(monsterList[i]->name);
            free(monsterList[i]->element);

            // free monster struct
            free(monsterList[i]);
        }
        free (monsterList);
    }