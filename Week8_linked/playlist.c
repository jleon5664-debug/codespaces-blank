#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "playlist.h"

// code logic
void playlist_init(Playlist *pl) {
    if (pl == NULL) return;
    pl->head = NULL;
    pl->tail = NULL;
    pl->count = 0;
}

void playlist_free(Playlist *pl) {
    if (pl == NULL) return;

    Song *cur = pl->head;
    while (cur != NULL) {
        Song *next = cur->next;
        free(cur);
        cur = next;
    }
    pl->head = NULL;
    pl->tail = NULL;
    pl->count = 0;
}

int playlist_append(Playlist *pl, const char *title, const char *artist, int duration_sec) {
    if (pl == NULL || title == NULL || artist == NULL) {
        return -1;
    }
    Song *node = malloc(sizeof(Song));
    if (node == NULL) {
        fprintf(stderr, "Out of memory\n");
        return -1;
    }

    // copy string
    strncpy(node->title, title, 63);
    node->title[63] = '\0';
    strncpy(node->artist, artist, 63);
    node->artist[63] = '\0';
    node->duration_sec = duration_sec;
    node->prev = NULL;
    node->next = NULL;

    if (pl->tail == NULL) {
        // empty list
        pl->head = node;
        pl->tail = node;
    } else {
        // add to end
        node->prev = pl->tail;
        pl->tail->next = node;
        pl->tail = node;
    }
    // update track list
    pl->count++;
    return 0;
}

void playlist_print(const Playlist *pl) {
    if (pl == NULL) {
        printf("= Playlist (0 songs) =\n");
        // guardrail for empty or invalid 
        return;
    }
    printf("= Playlist (%i songs) =\n", pl->count);
    Song *current = pl->head;
    int index = 1;

    while (current != NULL) {
        int mins = current->duration_sec / 60;
        int secs = current->duration_sec % 60;
        
        // output format Title - Artist [M:SS]
        printf("%i. %s - %s [%i:%02i]\n", index, current->title, current->artist, mins, secs);

        // increment
        index++;
        current = current->next;
    }
}

int playlist_load(Playlist *pl, const char *path) {
    if (pl == NULL || path == NULL) return -1;
}


// p free
// p load


// p save
// p prepend
// p remove
// p insert after
// p move up
// p print rev
// p total duration
