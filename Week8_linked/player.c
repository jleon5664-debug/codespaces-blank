#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "playlist.h"

// remove newline \n from fgets
    static void trim_newline(char *s) {
        size_t len = strlen(s);
        if (len > 0 && s[len-1] == '\n') {
        s[len-1] = '\0';
        }
    }

// skip leading spaces
    static char *skip_spaces(char *s) {
        while (*s && isspace((unsigned char)*s)) s++;
        return s;
    }

    int main(int argc, char *argv[]) {
        if (argc != 2) {
            fprintf(stderr, "Usage: %s <playlist_file>\n", argv[0]);
            return 1;
        }

    const char *file = argv[1];
        Playlist pl;
        playlist_init(&pl);
        // Load existing playlist
        playlist_load(&pl, file);

        char line[512];

    while (1) {
        printf("> ");
        fflush(stdout);

        if (fgets(line, sizeof(line), stdin) == NULL) {
            break;
        }
        trim_newline(line);

        // Skip empty lines/spaces
        char *cmd = skip_spaces(line);
        if (*cmd == '\0') continue;

        // Extract first word/command
        char *args = cmd;
        // cast unsigned to avoid negative/undef
        while (*args && !isspace((unsigned char)*args)) args++;
        if (*args) {
        // terminate string & move 
            *args = '\0';  
            args++;        
            args = skip_spaces(args);
        }

        // commands
        if (strcmp(cmd, "p") == 0) {
            playlist_print(&pl);
        }
        else if (strcmp(cmd, "r") == 0) {
            playlist_print_reverse(&pl);
        }
        else if (strcmp(cmd, "t") == 0) {
            int total = playlist_total_duration(&pl);
            if (total < 3600) {
        // time conversions
                printf("Total: %i:%02i\n", total / 60, total % 60);
            } else {
                printf("Total: %i:%02i:%02i\n",
                       total / 3600,
                       (total % 3600) / 60,
                       total % 60);
            }
        }
        else if (strcmp(cmd, "q") == 0) {
            if (playlist_save(&pl, file) != 0) {
                fprintf(stderr, "Error saving playlist\n");
            }
            break; 
        }
        else if (strcmp(cmd, "a") == 0 || strcmp(cmd, "pre") == 0) {
            // Format: title |artist | seconds
            char *title = strtok(args, "|");
            char *artist = strtok(NULL, "|");
            char *secs = strtok(NULL, "|");

            if (!title || !artist || !secs) {
            printf("Invalid format. Use: %s title|artist|seconds\n", cmd);
                continue;
            }

            int duration = atoi(secs);
            if (strcmp(cmd, "a") == 0) {
                playlist_append(&pl, title, artist, duration);
            } else {
                playlist_prepend(&pl, title, artist, duration);
            }
        }
        else if (strcmp(cmd, "ins") == 0) {
            // Format: after_title | title | artist | seconds
            char *after = strtok(args, "|");
            char *title = strtok(NULL, "|");
            char *artist = strtok(NULL, "|");
            char *secs = strtok(NULL, "|");

            if (!after || !title || !artist || !secs) {
                printf("Invalid format. Use: ins after_title|title|artist|seconds\n");
                continue;
            }

            int duration = atoi(secs);
            if (playlist_insert_after(&pl, after, title, artist, duration) != 0) {
                printf("Not found: \"%s\"\n", after);
            }
        }
            else if (strcmp(cmd, "del") == 0) {
            if (*args == '\0') {
                printf("Usage: del title\n");
                continue;
            }
            if (playlist_remove(&pl, args) != 0) {
                printf("Not found: \"%s\"\n", args);
            }
        }
        else if (strcmp(cmd, "up") == 0) {
            if (*args == '\0') {
                printf("Usage: up title\n");
                continue;
            }
            if (playlist_move_up(&pl, args) != 0) {
                printf("Not found: \"%s\"\n", args);
            }
        }
        else {
            printf("Unknown command. Type 'p' to print.\n");
        }
    }

        playlist_free(&pl);
        return 0;
}