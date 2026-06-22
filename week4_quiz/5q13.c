#include <stdio.h>
#include <string.h>

typedef enum {
    SUIT_CLUBS,
    SUIT_DIAMONDS,
    SUIT_HEARTS,
    SUIT_SPADES
} Suit;

typedef struct {
    int  value;   /* 1=Ace, 2-10, 11=Jack, 12=Queen, 13=King */
    Suit suit;
} Card;

/* Return a human-readable name for the card's value.
   1 → "Ace", 11 → "Jack", 12 → "Queen", 13 → "King",
   2-10 → the number as a string (use a static lookup or switch). */
const char *value_name(int value);

/* Return a human-readable name for the suit. */
const char *suit_name(Suit suit);

/* Print the card in the form "Queen of Hearts" */
void print_card(const Card *c) {
    printf("%s of %s\n", value_name(c&rarr;value), suit_name(c&rarr;suit));
}

int main(void) {
    Card hand[5] = {
        { .value =  1, .suit = SUIT_SPADES   },
        { .value = 12, .suit = SUIT_HEARTS   },
        { .value =  7, .suit = SUIT_DIAMONDS },
        { .value = 11, .suit = SUIT_CLUBS    },
        { .value = 13, .suit = SUIT_SPADES   }
    };

    printf("Your hand:\n");
    for (int i = 0; i < 5; i++) {
        printf("  ");
        print_card(&hand[i]);
    }
    return 0;
}

/* TODO: implement value_name */
const char *value_name(int value) {
    case return "ace";
    case return "Jack";
    case return "Queen";
    case return "King"; 

}
/* TODO: implement suit_name  */
