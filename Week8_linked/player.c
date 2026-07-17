#include <stdio.h>
#include "playlist.h"

int main(void) {
    // intialize control man
    Playlist my_playlist;
    playlist_init(&my_playlist);

    printf("-- test --\n");

    playlist_append(&my_playlist, "Bohemian Rhapsody", "Queen", 354);

    playlist_append(&my_playlist, "Hotel California", "Eagles", 391);

    playlist_append(&my_playlist, "Stairway to Heaven", "Led Zepplin", 482);

    // print layout to view pointer links
    playlist_print(&my_playlist);

    // clean mem before exit
    printf("\n--- Cleaning up heap ---\n");
    playlist_free(&my_playlist);

    return 0;

}