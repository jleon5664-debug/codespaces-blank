#ifndef PLAYLIST_H
#define PLAYLIST_H

/* A single song node */
typedef struct Song {
    char         title[64];
    char         artist[64];
    int          duration_sec;
    struct Song *prev;
    struct Song *next;
} Song;

/* Doubly-linked list header */
typedef struct {
    Song *head;
    Song *tail;
    int   count;
} Playlist;

/* --- Lifecycle --- */
void playlist_init(Playlist *pl);
void playlist_free(Playlist *pl);

/* --- Mutation --- */
/* Append song to back. 0 = ok. */
int playlist_append(
    Playlist   *pl,
    const char *title,
    const char *artist,
    int         duration_sec
);

/* Prepend song to front. 0 = ok. */
int playlist_prepend(
    Playlist   *pl,
    const char *title,
    const char *artist,
    int         duration_sec
);

/* Insert after song with matching
   title. Returns 0 on success,
   -1 if title not found. */
int playlist_insert_after(
    Playlist   *pl,
    const char *after_title,
    const char *title,
    const char *artist,
    int         duration_sec
);

/* Remove first song matching
   title. Returns 0 or -1. */
int playlist_remove(
    Playlist   *pl,
    const char *title
);

/* Move song one position toward
   front. No-op if already first.
   Returns 0 or -1 if not found. */
int playlist_move_up(
    Playlist   *pl,
    const char *title
);

/* --- Query --- */
/* Print all songs, numbered */
void playlist_print(
    const Playlist *pl
);

/* Print in reverse order */
void playlist_print_reverse(
    const Playlist *pl
);

/* Return total duration in sec */
int playlist_total_duration(
    const Playlist *pl
);

/* --- File I/O (from week 7) --- */
/* Load from file. 0 or -1. */
int playlist_load(
    Playlist   *pl,
    const char *path
);

/* Save to file. 0 or -1. */
int playlist_save(
    const Playlist *pl,
    const char     *path
);

#endif