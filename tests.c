#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "snake.h"

#define SMAX 1000000

bool run_test(FILE *path, Position pos, const Position apple, const int A, const int B) {
    int x0 = pos.x, y0 = pos.y;
    Position start = {x0, y0};
    long long total = search(path, &start, apple, A, B), max = 35 * A * B;
    if (total < 0) {
        fprintf(stderr, "Failed to find apple for start at (%d, %d), apple at (%d, %d) and screen size of %d x %d.\n",
                x0, y0, apple.x, apple.y, A, B);
        printf("!");
        return false;
    }
    if (total > max) {
        fprintf(
            stderr,
            "Took too many moves to find the apple for start at (%d, %d), apple at (%d, %d) and screen size of %d x %d.   %lld > 35 * %d = %lld\n",
            x0, y0, apple.x, apple.y, A, B, total, A * B, max);
        printf("!");
        return false;
    }
    //printf("#");
    return true;
}

int main() {
    int passed, total;

    passed = 0;
    total = 10000;
    unsigned int seed = time(nullptr);
    printf("Running %d tests...\n", total);
    for (int i = 0; i < total; i++) {
        seed++;
        int A = rand_r(&seed) % SMAX + 1, B = rand_r(&seed) % (SMAX / A) + 1, x0 = rand_r(&seed) % A + 1, y0 =
                rand_r(&seed) % B + 1, xa = rand_r(&seed) % A + 1, ya = rand_r(&seed) % B + 1;
        Position pos, apple;
        pos.x = x0, pos.y = y0;
        apple.x = xa, apple.y = ya;
        FILE *path = fopen("path.txt", "r");
        if (!path) {
            fprintf(stderr, "Failed to open file.\n");
            return 1;
        }
        if (run_test(path, pos, apple, A, B)) {
            passed++;
        }
        fclose(path);
    }
    printf("Passed %d / %d tests.\n", passed, total);

    return 0;
}
