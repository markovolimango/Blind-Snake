#include <stdio.h>
#include "snake.h"

#define SMAX 1000000

int main(void) {
    int x_start, y_start, x_apple, y_apple, A, B;
    Position pos, apple;
    scanf("%d %d %d %d %d %d", &A, &B, &x_start, &y_start, &x_apple, &y_apple);
    pos.x = x_start;
    pos.y = y_start;
    apple.x = x_apple;
    apple.y = y_apple;
    FILE *path = fopen("path.txt", "r");

    if (A * B > SMAX) {
        fprintf(stderr, "Screen size out of bounds.\n");
        return 1;
    }
    if (!path) {
        fprintf(stderr, "Failed to open file.\n");
        return 1;
    }
    if (x_apple > A || x_apple < 0 || y_apple > B || y_apple < 0) {
        fprintf(stderr, "Apple out of bounds.\n");
        return 1;
    }
    if (x_start > A || x_start < 0 || y_start > B || y_start < 0) {
        fprintf(stderr, "Starting position out of bounds.\n");
        return 1;
    }

    const long long count = find_apple(path, &pos, apple, A, B), max = 35 * A * B;
    if (count > 0) {
        printf("Found after %lld moves", count);
        if (count > max) {
            printf(", which is greater than 35 * %d * %d = %lld. Fail...\n", A, B, max);
        } else {
            printf(". Success!");
        }
    } else {
        printf("Not found after %lld moves. Ended up at (%d, %d). Fail...\n", -count, pos.x, pos.y);
    }
    fclose(path);
    return 0;
}
