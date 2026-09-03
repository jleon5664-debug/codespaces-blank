// implementation of the code logic
#include <stdio.h>
#include "main.h"

// forward
void printMonsterFields(Monster *m);

int main(void) {
    Monster monsters[MAX_MONSTERS];
    int count = 0;
    int train_index = 0;

// input all monsters data
    readAllMonsters(monsters, &count);

// input zero training index from final line
    scanf("%i", &train_index);

// print initial monster data
    printAllMonster(monsters, count);

// change target monster
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

// readallM
void readAllMonsters(Monster monsters[], int *count) {
    int n;
    scanf("%i", &n);
    *count = n;

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
// display monster attributes
void printMonsterFields(Monster *m) {
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
        for (int i = 0; i < count; i++) {
            printf("Monster %i:\n", i);
            printMonsterFields(&monsters[i]);
            printf("\n");
        }
    }
// train
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
        if (score > bestScore) {
            bestScore = score;
            bestIndex = i;
        }
    }
    return bestIndex;
}
