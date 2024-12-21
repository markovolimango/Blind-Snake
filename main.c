#include <stdio.h>
#include "snake.h"

#define SMAX 1000000

int main(void) {
    int x0, y0, xa, ya, A, B;
    Position pos, apple;
    scanf("%d %d %d %d %d %d", &A, &B, &x0, &y0, &xa, &ya);
    pos.x = x0;
    pos.y = y0;
    apple.x = xa;
    apple.y = ya;
    FILE *path = fopen("path.txt", "r");

    if (A * B > SMAX) {
        fprintf(stderr, "Screen size out of bounds.\n");
        return 1;
    }
    if (!path) {
        fprintf(stderr, "Failed to open file.\n");
        return 1;
    }
    if (xa > A || xa < 0 || ya > B || ya < 0) {
        fprintf(stderr, "Apple out of bounds.\n");
        return 1;
    }
    if (x0 > A || x0 < 0 || y0 > B || y0 < 0) {
        fprintf(stderr, "Starting position out of bounds.\n");
        return 1;
    }

    const long long count = search(path, &pos, apple, A, B);
    if (count > 0) {
        printf("Found after %lld moves.\n", count);
    } else {
        printf("Not found after %lld moves. Ended up at (%d, %d).\n", -count, pos.x, pos.y);
    }
    fclose(path);
    return 0;
}
