#include <stdio.h>
#include <stdlib.h>

char invert(char c) {
    if (c == 'd')
        return 'u';
    if (c == 'r')
        return 'l';
    if (c == 'u')
        return 'd';
    if (c == 'l')
        return 'r';
    fprintf(stderr, "Invalid character %c\n", c);
    return 0;
}

void generate_path(FILE *path, int S) {
    char *moves_dir = malloc(2 * S * sizeof(char));
    int *moves_count = malloc(2 * S * sizeof(int));

    if (!moves_dir || !moves_count) {
        fprintf(stderr, "Memory allocation failed\n");
        free(moves_dir);
        free(moves_count);
        return;
    }

    int x = 1, y = S, n = 0;
    char last_move = 'd';
    int move_count = 0;

    while (x != S) {
        if (x + 1 <= S / y) {
            x++;
            if (last_move == 'd') {
                moves_dir[n] = last_move;
                moves_count[n] = move_count;
                n++;
                fprintf(path, "%c%d", 'd', move_count);
                move_count = 1;
                last_move = 'r';
            } else {
                move_count++;
            }
        } else {
            y--;
            if (last_move == 'r') {
                moves_dir[n] = last_move;
                moves_count[n] = move_count;
                n++;
                fprintf(path, "%c%d", 'r', move_count);
                move_count = 1;
                last_move = 'd';
            } else {
                move_count++;
            }
        }
    }
    moves_dir[n] = last_move;
    moves_count[n] = move_count;
    n++;
    fprintf(path, "%c%d", last_move, move_count);

    int start = 0, end = n;
    while (start < end) {
        fprintf(path, "%c%d", invert(moves_dir[end - 1]), moves_count[end - 1] + 1);
        end -= 2;
        start += 2;
        for (int i = end - 1; i >= start; i--) {
            fprintf(path, "%c%d", invert(moves_dir[i]), moves_count[i]);
        }
        if (start >= end)
            break;
        fprintf(path, "%c%d", moves_dir[start], moves_count[start] + 1);
        start += 2;
        end -= 2;
        for (int i = start; i < end; i++) {
            fprintf(path, "%c%d", moves_dir[i], moves_count[i]);
        }
    }

    free(moves_dir);
    free(moves_count);
}

int main(void) {
    FILE *path = fopen("path.txt", "w");
    if (!path) {
        fprintf(stderr, "Failed to open file\n");
        return 1;
    }

    int S = 16;
    generate_path(path, S);
    fclose(path);
    return 0;
}
