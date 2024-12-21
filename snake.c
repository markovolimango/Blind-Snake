#include <stdio.h>
#include "snake.h"

bool send_signal(const char signal, Position *pos, const Position apple, const int A, const int B) {
    if (signal == 'l') {
        if (pos->x != 1)
            pos->x--;
        else
            pos->x = A;
    } else if (signal == 'r') {
        if (pos->x != A)
            pos->x++;
        else
            pos->x = 1;
    } else if (signal == 'd') {
        if (pos->y != 1)
            pos->y--;
        else
            pos->y = B;
    } else if (signal == 'u') {
        if (pos->y != B)
            pos->y++;
        else
            pos->y = 1;
    } else {
        fprintf(stderr, "Invalid signal %c.\n", signal);
    }
    return pos->x == apple.x && pos->y == apple.y;
}

long long search(FILE *path, Position *pos, const Position apple, const int A, const int B) {
    char c = fgetc(path);
    int move_count = 0;
    long long total = 0;
    while (c != '*') {
        const char move_dir = c;
        move_count = 0;
        c = fgetc(path);
        while (c >= '0' && c <= '9') {
            move_count = move_count * 10 + c - '0';
            c = fgetc(path);
        }
        for (int i = 0; i < move_count; i++) {
            total++;
            if (send_signal(move_dir, pos, apple, A, B)) {
                return total;
            }
        }
    }
    return -total;
}
