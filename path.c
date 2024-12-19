#include <stdio.h>

#define NMAX 2000

void move(int *x, int *y, char dir) {
    switch (dir) {
        case 'r':
            *x = *x + 1;
            break;
        case 'l':
            *x = *x - 1;
            break;
        case 'u':
            *y = *y + 1;
            break;
        case 'd':
            *y = *y - 1;
            break;
    }
}

bool contains(int a[], int x, int n) {
    for (int i = 0; i < n; i++) {
        if (a[i] == x)
            return true;
    }
    return false;
}

void generate_path(FILE *path, int S) {
    long long count = 0;
    int x = 1, y = S;
    int in_length = 0, in[NMAX], out_length = 0, out[NMAX];
    char last_move = '/';
    while (x != S) {
        count++;
        if (x + 1 <= S / y) {
            if (last_move == 'd') {
                in[in_length++] = y - x;
            }
            x++;
            last_move = 'r';
            fprintf(path, "r");
        } else {
            if (last_move == 'r') {
                out[out_length++] = y - x;
            }
            y--;
            last_move = 'd';
            fprintf(path, "d");
        }
    }

    bool going_up = true, bonus = true;;
    x--;
    last_move = 'l';
    int in_start = 0, in_end = in_length, out_start = 0, out_end = out_length;
    int i = in_end - 1, j = out_end - 1;
    while (x != 1 || y != 1) {
        count++;
        fputc(last_move, path);
        if (going_up) {
            if (contains(in, y - x, in_length)) {
                if (!bonus) {
                    y++;
                    last_move = 'u';
                } else {
                    bonus = false;
                    x--;
                    last_move = 'l';
                }
            } else if (contains(out, y - x, out_length)) {
                if (x == 1) {
                    going_up = false;
                    bonus = true;
                    y--;
                    last_move = 'd';
                    continue;
                }
                x--;
                last_move = 'l';
            } else {
                move(&x, &y, last_move);
            }
        } else {
            if (contains(in, y - x, in_length)) {
                if (!bonus) {
                    x++;
                    last_move = 'r';
                } else {
                    bonus = false;
                    y--;
                    last_move = 'd';
                }
            } else if (contains(out, y - x, out_length)) {
                if (y == 1) {
                    going_up = true;
                    bonus = true;
                    x--;
                    last_move = 'l';
                    continue;
                }
                y--;
                last_move = 'd';
            } else {
                move(&x, &y, last_move);
            }
        }
    }
    fputc(last_move, path);
    printf("%lld\n", count);
}

int main(void) {
    FILE *path = fopen("path.txt", "w");
    int S = 25;
    generate_path(path, S);
    return 0;
}
