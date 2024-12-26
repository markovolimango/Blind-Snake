#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char direction;
    unsigned count;
} Move;

char invert_dir(char direction) {
    switch (direction) {
        case 'd':
            return 'u';
        case 'r':
            return 'l';
        case 'u':
            return 'd';
        case 'l':
            return 'r';
        default:
            fprintf(stderr, "Invalid direction %c.\n", direction);
            return 0;
    }
}

void generate_path(FILE *path, int S, bool isRight) {
    Move *moves = malloc(2 * S * sizeof(Move));
    if (!moves) {
        fprintf(stderr, "Memory allocation failed\n");
        free(moves);
        return;
    }

    int x = 1, y = S, moves_len = 0;
    char side_move = isRight ? 'r' : 'l';
    Move move;
    move.direction = 'd';
    move.count = 1;
    while (x != S) {
        if (x + 1 <= S / y) {
            x++;
            if (move.direction == 'd') {
                moves[moves_len] = move;
                moves_len++;
                move.count = 1;
                move.direction = side_move;
            } else {
                move.count++;
            }
        } else {
            y--;
            if (move.direction == side_move) {
                moves[moves_len] = move;
                moves_len++;
                move.count = 1;
                move.direction = 'd';
            } else {
                move.count++;
            }
        }
    }
    moves[moves_len].direction = move.direction;
    moves[moves_len].count = move.count;
    moves_len++;

    int start = moves_len / 2 - 2, end = moves_len / 2 + 2;
    bool going_up = 1;
    while (start >= 0 && end <= moves_len) {
        if (going_up) {
            fprintf(path, "%c%d", moves[end - 1].direction, moves[end - 1].count + 1);
            for (int i = end - 1; i >= start; i--) {
                fprintf(path, "%c%d", invert_dir(moves[i].direction), moves[i].count);
            }
            start -= 2;
            end += 2;
            going_up = 0;
        } else {
            fprintf(path, "%c%d", invert_dir(moves[start].direction), moves[start].count + 1);
            for (int i = start; i < end; i++) {
                fprintf(path, "%c%d", moves[i].direction, moves[i].count);
            }
            start -= 2;
            end += 2;
            going_up = 1;
        }
    }
    free(moves);
}

int main(void) {
    FILE *path = fopen("path.txt", "w");
    if (!path) {
        fprintf(stderr, "Failed to open file\n");
        return 1;
    }

    int S = 1000000;
    generate_path(path, 2916, true);
    generate_path(path, 49729, false);
    generate_path(path, 320356, true);
    generate_path(path, S, false);
    fprintf(path, "*");
    fclose(path);
    return 0;
}
