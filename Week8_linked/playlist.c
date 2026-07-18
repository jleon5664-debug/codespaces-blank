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


    FILE *fp = fopen(path, "r");
    if (fp == NULL) {
        // file dne
        return 0;
    }

    char line [256];
    while (fgets(line, sizeof(line), fp) != NULL) {
        //remove \n
        line[strcspn(line, "\n")] = '\0';

        // skip blank lines
        if (strlen(line) == 0) 
        continue;
        
        // parse |
        char *title = strtok(line, "|");
        char *artist = strtok(NULL, "|");
        char *dur_str = strtok(NULL, "|");

        if (title == NULL || artist == NULL || dur_str == NULL) 
        continue;

        int duration = atoi(dur_str);

        // reuse append
        playlist_append(pl, title, artist, duration);
    }
    fclose(fp);
    return 0;
}

int playlist_save(const Playlist *pl, const char *path) {
    if (pl == NULL || path == NULL)
    return -1;

    FILE *fp = fopen(path, "w");
    if (fp == NULL) {
        perror("Error opening file for writing");
        return -1;
    }

    Song *cur = pl->head;
    while (cur != NULL) {
        fprintf(fp, "%s|%s|%i\n", cur->title, cur->artist, cur->duration_sec);

        cur = cur->next;
    }
    fclose(fp);
    return 0;
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
