#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "snake.h"

#define SMAX 1000000

bool run_test(FILE *path, Position pos, const Position apple, const int A, const int B) {
    int x0 = pos.x, y0 = pos.y;
    Position start = {x0, y0};
    long long total = find_apple(path, &start, apple, A, B), max = 35 * A * B;
    if (total < 0) {
        fprintf(stderr, "Failed to find apple for start at (%d, %d), apple at (%d, %d) and screen size of %d x %d.\n",
                x0, y0, apple.x, apple.y, A, B);
        return false;
    }
    if (total > max) {
        //fprintf(
        //    stderr,
        //    "Took too many moves to find the apple for start at (%d, %d), apple at (%d, %d) and screen size of %d x %d.   %lld > 35 * %d = %lld\n",
        //    x0, y0, apple.x, apple.y, A, B, total, A * B, max);
        return false;
    }
    return true;
}

void run_random_tests(int total) {
    int passed = 0;
    unsigned int seed = time(nullptr);
    printf("Running %d random tests...\n", total);
    for (int i = 0; i < total; i++) {
        seed++;
        int S = rand_r(&seed) % SMAX, A = 1 + rand_r(&seed) % ((int) sqrt(S)), B = S / A, x0 = 1 + rand_r(&seed) % A, y0
                = 1 + rand_r(&seed) % B, xa = 1 + rand_r(&seed) % A, ya = 1 + rand_r(&seed) % B;
        Position pos, apple;
        pos.x = x0, pos.y = y0;
        apple.x = xa, apple.y = ya;
        FILE *path = fopen("path.txt", "r");
        if (!path) {
            fprintf(stderr, "Failed to open file.\n");
            return;
        }
        if (run_test(path, pos, apple, A, B)) {
            passed++;
        }
        fclose(path);
    }
    printf("Passed %d / %d random tests.\n", passed, total);
}

void run_edge_corner_tests(int total) {
    int passed = 0;
    unsigned int seed = time(nullptr);
    printf("Running %d edge tests...\n", total);
    for (int i = 0; i < total; i++) {
        seed++;
        int S = rand_r(&seed) % SMAX, A = 1, B = 1, x0 = 1, y0 = 1, xa = 1, ya = 1, dir = rand_r(&seed) % 2;
        if (dir) {
            A = S;
            xa = S;
        } else {
            B = S;
            ya = S;
        }
        Position pos, apple;
        pos.x = x0, pos.y = y0;
        apple.x = xa, apple.y = ya;
        FILE *path = fopen("path.txt", "r");
        if (!path) {
            fprintf(stderr, "Failed to open file.\n");
            return;
        }
        if (run_test(path, pos, apple, A, B)) {
            passed++;
        }
        fclose(path);
    }
    printf("Passed %d / %d edge tests.\n", passed, total);
}

void run_random_edge_tests(int total) {
    int passed = 0;
    unsigned int seed = time(nullptr);
    printf("Running %d random edge tests...\n", total);
    for (int i = 0; i < total; i++) {
        seed++;
        int S = rand_r(&seed) % SMAX, A = 1, B = 1, x0 = 1, y0 = 1, xa = 1, ya = 1, dir = rand_r(&seed) % 2;
        if (dir) {
            A = S;
            x0 = 1 + rand_r(&seed) % A;
            xa = 1 + rand_r(&seed) % A;
        } else {
            B = S;
            y0 = 1 + rand_r(&seed) % B;
            ya = 1 + rand_r(&seed) % B;
        }
        Position pos, apple;
        pos.x = x0, pos.y = y0;
        apple.x = xa, apple.y = ya;
        FILE *path = fopen("path.txt", "r");
        if (!path) {
            fprintf(stderr, "Failed to open file.\n");
            return;
        }
        if (run_test(path, pos, apple, A, B)) {
            passed++;
        }
        fclose(path);
    }
    printf("Passed %d / %d random edge tests.\n", passed, total);
}

void run_random_square_tests(int total) {
    int passed = 0;
    unsigned int seed = time(nullptr);
    printf("Running %d random square tests...\n", total);
    for (int i = 0; i < total; i++) {
        seed++;
        int S = rand_r(&seed) % SMAX, A = (int) sqrt(S), B = S / A, x0 = 1 + rand_r(&seed) % A, y0
                = 1 + rand_r(&seed) % B, xa = 1 + rand_r(&seed) % A, ya = 1 + rand_r(&seed) % B;
        Position pos, apple;
        pos.x = x0, pos.y = y0;
        apple.x = xa, apple.y = ya;
        FILE *path = fopen("path.txt", "r");
        if (!path) {
            fprintf(stderr, "Failed to open file.\n");
            return;
        }
        if (run_test(path, pos, apple, A, B)) {
            passed++;
        }
        fclose(path);
    }
    printf("Passed %d / %d random square tests.\n", passed, total);
}

void run_square_corner_tests(int total) {
    int passed = 0;
    unsigned int seed = time(nullptr);
    printf("Running %d square tests...\n", total);
    for (int i = 0; i < total; i++) {
        seed++;
        int S = rand_r(&seed) % SMAX, A = (int) sqrt(S), B = S / A, x0 = 1, y0 = 1, xa = A, ya = B;
        Position pos, apple;
        pos.x = x0, pos.y = y0;
        apple.x = xa, apple.y = ya;
        FILE *path = fopen("path.txt", "r");
        if (!path) {
            fprintf(stderr, "Failed to open file.\n");
            return;
        }
        if (run_test(path, pos, apple, A, B)) {
            passed++;
        }
        fclose(path);
    }
    printf("Passed %d / %d square tests.\n", passed, total);
}

void run_corner_tests(int total) {
    int passed = 0;
    unsigned int seed = time(nullptr);
    printf("Running %d corner tests...\n", total);
    for (int i = 0; i < total; i++) {
        seed++;
        int S = rand_r(&seed) % SMAX, A = 1 + rand_r(&seed) % ((int) sqrt(S)), B = S / A, x0 = 1, y0 = 1, xa = A, ya =
                B;
        Position pos, apple;
        pos.x = x0, pos.y = y0;
        apple.x = xa, apple.y = ya;
        FILE *path = fopen("path.txt", "r");
        if (!path) {
            fprintf(stderr, "Failed to open file.\n");
            return;
        }
        if (run_test(path, pos, apple, A, B)) {
            passed++;
        }
        fclose(path);
    }
    printf("Passed %d / %d corner tests.\n", passed, total);
}

void run_random_corner_tests(int total) {
    int passed = 0;
    unsigned int seed = time(nullptr);
    printf("Running %d random corner tests...\n", total);
    for (int i = 0; i < total; i++) {
        seed++;
        int S = rand_r(&seed) % SMAX, A = 1 + rand_r(&seed) % ((int) sqrt(S)), B = S / A, x0 = 1, y0 = 1, xa =
                1 + rand_r(&seed) % A, ya = 1 + rand_r(&seed) % B;
        Position pos, apple;
        pos.x = x0, pos.y = y0;
        apple.x = xa, apple.y = ya;
        FILE *path = fopen("path.txt", "r");
        if (!path) {
            fprintf(stderr, "Failed to open file.\n");
            return;
        }
        if (run_test(path, pos, apple, A, B)) {
            passed++;
        }
        fclose(path);
    }
    printf("Passed %d / %d random corner tests.\n", passed, total);
}

int main() {
    int count;
    scanf("%d", &count);
    //everything is random
    run_random_tests(count);
    printf("\n");

    //A=B, everything else is random
    run_random_square_tests(count);
    //x0=y0, A=B, xa=A ya=B, S is random
    run_square_corner_tests(count);
    printf("\n");

    //A=1 or B=1, everything else is random
    run_random_edge_tests(count);
    //x0=y0=1, A=1 xa=1 ya=B or B=1 xa=A ya=1, S is random
    run_edge_corner_tests(count);
    printf("\n");

    //x0=y0=1, everything else is random
    run_random_corner_tests(count);
    //x0=y0=1, xa=A ya=B, everything else is random
    run_corner_tests(count);
    printf("\n");
    return 0;
}
