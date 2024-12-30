#include <stdio.h>
#include <stdlib.h>

//one move struct is a direction and the number of moves the snake should make in that direction, for easier memorisation
typedef struct {
    char direction;
    unsigned count;
} Move;

//this will be used in the main path generation function, because it will trace one path form the top right to the
//bottom left, then repeat it while inverting it every time
char invert_dir(const char direction) {
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

//this function generates the path under one set S, and will be called multiple times (for different values of S) when
//generating the complette path
void generate_path(FILE *path, int S, bool isRight) {
    //this array will store all the moves from the top left to the bottom right corner if movesRight is true, and from
    //the top right to the bottom left corner if it's true
    Move *moves = malloc(2 * S * sizeof(Move));
    if (!moves) {
        fprintf(stderr, "Memory allocation failed.\n");
        free(moves);
        return;
    }

    int x = 1, y = S, moves_len = 0;
    char side_move = isRight ? 'r' : 'l';
    Move move;
    move.direction = 'd';
    move.count = 1;

    //this loop just goes under the line y = S / x, and remembers all the moves made
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
    //just adding the last move that wasn't added in the loop
    moves[moves_len].direction = move.direction;
    moves[moves_len].count = move.count;
    moves_len++;

    //since the snake should start at (1, 1) and move outward, we start with two pointers in the middle of the array,
    //and then move towards the ends of the array
    //this will create the desired path, as one curve will always be exactly below the next one and above the previous one
    //going_up is just used to alternate the path between going up and down
    int start = moves_len / 2 - 2, end = moves_len / 2 + 2;
    bool going_up = 1;
    while (start >= 0 && end <= moves_len) {
        if (going_up) {
            //this first move connects the end of the last curve with the start of this one
            fprintf(path, "%c%d", moves[end - 1].direction, moves[end - 1].count + 1);

            for (int i = end - 1; i >= start; i--) {
                fprintf(path, "%c%d", invert_dir(moves[i].direction), moves[i].count);
            }
            start -= 2;
            end += 2;
            going_up = 0;
        } else {
            //this is also the move that connects the end to the start
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

    //these numbers where chosen after some testing and they seem pretty optimal
    generate_path(path, 2916, true);
    generate_path(path, 50176, false);
    generate_path(path, 320356, true);
    generate_path(path, 1000000, false);
    fprintf(path, "*");
    fclose(path);

    printf("Path successfully generated.\n");
    return 0;
}
