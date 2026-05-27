#include <stdio.h>
#include <stdlib.h>

void print_hero_stats(void);
void print_monster_stats(void);
double calculate_damage(int, int, int);

int hero_bravery = 10;
int hero_attack = 10;
int hero_defense = 10;
double hero_health = 10;
char hero_name[50];

int monster_attack = 12;
int monster_defense = 10;
double monster_health = 10;
char monster_name[50] = "Decepticon";


int main(void) {
    printf("===================================\n");
    printf("|   Legally Distinct from Zelda   |\n");
    printf("|            the sequel           |\n");
    printf("|=================================|\n");
    
    printf("Enter your hero's name> ");
    fscanf(stdin, "%s", hero_name);

    do {
        printf("%s Attacks!\n", hero_name);
        monster_health -= calculate_damage(hero_bravery, hero_attack, monster_defense);
        if (monster_health < 0) monster_health = 0;
        printf("%s Counter-Attacks!\n", monster_name);
        hero_health -= calculate_damage(0, monster_attack, hero_defense);
        if (hero_health < 0) hero_health = 0;

        print_hero_stats();
        print_monster_stats();
        printf("Enter 'd' to continue");
        char enter;
        fscanf(stdin, "%c", &enter);

    } while (hero_health > 0 && monster_health > 0);
    
    if (hero_health == 0 && monster_health == 0) {
        printf("DRAW!\n");
    } else if (hero_health == 0 && monster_health > 0) {
        printf("%s WINS!\n", monster_name);
    } else {
        printf("%s WINS!\n", hero_name);
    };


    
}

void print_hero_stats(void) {
    printf("====================\n");
    printf("| %-18s|\n", hero_name);
    printf("| HP: %lf            |\n", hero_health);
    printf("| ATTACK: %d DEF: %d|\n", hero_attack, hero_defense);
    printf("| BRAVERY: %d.      |\n", hero_bravery);
    printf("====================|\n");
};

void print_monster_stats(void) {
    printf("====================\n");
    printf("| %-18s|\n", monster_name);
    printf("| HP: %lf            |\n", monster_health);
    printf("| ATTACK: %d DEF: %d|\n", monster_attack, monster_defense);
    printf("====================|\n");
};

double calculate_damage(int bravery, int attack, int defense) {
    float defense_modifier = 0.0;
    srand(0);
    defense_modifier = 1 + rand()%20;


    double adjusted_attack = attack * (1 + (double) bravery/100);
    printf("adjusted attack: %lf\n", adjusted_attack);
    double damage = adjusted_attack - defense;
    printf("damage: %lf\n", damage);
    return (damage < 0) ? 0 : damage;

}