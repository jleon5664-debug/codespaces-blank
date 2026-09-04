// implementation of the code logic
#include <stdio.h>
#include "main.h"

// forward declaration of attribute parameters
static void printMonsterFields(Monster *m);

int main(void) {
    // 100 slots reserved on stack
    Monster monsters[MAX_MONSTERS];
    int count = 0;
    int train_index = 0;

// intake monster data
    readAllMonsters(monsters, &count);

// read input data and pass 
    scanf("%i", &train_index);

// print initial monster data
    printAllMonster(monsters, count);

// evaluate & pass address of monsters[]
    trainMonster(&monsters[train_index]);

// training report
    printf("=== TRAINING ===\n");
    printf("Training Monster %i...\n", train_index);
    printMonsterFields(&monsters[train_index]);
// separate text block w \n 
    printf("\n");

// identify strongest monster then print attributes
    int strongest_index = findStrongest(monsters, count);
    printf("=== STRONGEST MONSTER ===\n");
    printMonsterFields(&monsters[strongest_index]);

    return 0;
}

// reads header integer
void readAllMonsters(Monster monsters[], int *count) {
    int n;
    scanf("%i", &n);
    // updates count
    *count = n;
    // pass strings & int address
    for (int i = 0; i < n; i++) {
        scanf("%s %s %i %i %i %i",
            monsters[i].name,
            monsters[i].type,
            &monsters[i].level,
            &monsters[i].hp,
            &monsters[i].attack,
        &monsters[i].defense);
    }
}
// display monster attributes & static for internal linkage 
static void printMonsterFields(Monster *m) {
    printf("Name: %s\n", m->name);
    printf("Type: %s\n", m->type);
    printf("Level: %i\n", m->level);
    printf("HP: %i\n", m->hp);
    printf("Attack: %i\n", m->attack);
    printf("Defense: %i\n", m->defense);
}
// print monster
void printAllMonster(Monster *monsters, int count) {
        printf("=== MONSTER TEAM ===\n");
        // track count, avoid print of unintialized memory 
        for (int i = 0; i < count; i++) {
            printf("Monster %i:\n", i);
            printMonsterFields(&monsters[i]);
            // separate blocks \n 
            printf("\n");
        }
    }
// mutate stack slot of monster w train data 
void trainMonster(Monster *monster) {
    int position = monster->name[0] - 'A' + 1;
    monster->level += 1;
    monster->hp += position;
    monster->attack += 5;
    monster->defense += 3;
}
// find strongest
int findStrongest(Monster monsters[], int count) {
    int bestIndex = 0;
    int bestScore = monsters[0].level + monsters[0].attack + monsters[0].defense;

    for (int i = 1; i < count; i++) {
        int score = monsters[i].level + monsters[i].attack + monsters[i].defense;
        // tie-breaker
        if (score > bestScore) {
            bestScore = score;
            bestIndex = i;
        }
    }
    return bestIndex;
}
