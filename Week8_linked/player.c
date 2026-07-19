#include <stdio.h>
#include "playlist.h"

int main(void) {
    Playlist pl;
    playlist_init(&pl);

    printf("--- Phase 1: Loading Baseline Dataset ---\n");
    playlist_load(&pl, "test.txt");
    playlist_print(&pl);

    printf("\n--- Phase 2: test mid-list insertion (after 'hotel california') ---\n");
    playlist_insert_after(&pl, "Hotel California", "Time", "Pink Floyd", 401);
    playlist_print(&pl);

    printf("\n--- Phase 3: Testing Tail-Boundary Insertion (After 'Come Together') ---\n");
    playlist_insert_after(&pl, "Come Together", "Hey Jude", "Beatles", 431);
    playlist_print(&pl);

    printf("\n--- Phase 4: Testing Nonexistent Target Handling ---\n");
    int status = playlist_insert_after(&pl, "Paranoid", "Iron Man", "Black Sabbath", 168);
    printf("Operation exit status (Expected -1): %i\n", status);

    printf("\n--- Phase 5: Executing Silent Deallocation ---\n");
    playlist_free(&pl);

    return 0;
}