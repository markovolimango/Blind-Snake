#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "snake.h"

#define SMAX 1000000

bool run_test(FILE *path, Position pos, const Position apple, const int A, const int B) {
    int x0 = pos.x, y0 = pos.y;
    Position start = {x0, y0};
    long long total = search(path, &start, apple, A, B), max = 35 * A * B;
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

int run_random_tests(int total) {
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
            return -1;
        }
        if (run_test(path, pos, apple, A, B)) {
            passed++;
        }
        fclose(path);
    }
    printf("Passed %d / %d random tests.\n", passed, total);
    return passed;
}

int run_edge_tests(int total) {
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
            return -1;
        }
        if (run_test(path, pos, apple, A, B)) {
            passed++;
        }
        fclose(path);
    }
    printf("Passed %d / %d edge tests.\n", passed, total);
    return passed;
}

int run_random_edge_tests(int total) {
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
            return -1;
        }
        if (run_test(path, pos, apple, A, B)) {
            passed++;
        }
        fclose(path);
    }
    printf("Passed %d / %d random edge tests.\n", passed, total);
    return passed;
}

int run_random_square_tests(int total) {
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
            return -1;
        }
        if (run_test(path, pos, apple, A, B)) {
            passed++;
        }
        fclose(path);
    }
    printf("Passed %d / %d random square tests.\n", passed, total);
    return passed;
}

int run_square_tests(int total) {
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
            return -1;
        }
        if (run_test(path, pos, apple, A, B)) {
            passed++;
        }
        fclose(path);
    }
    printf("Passed %d / %d square tests.\n", passed, total);
    return passed;
}

int run_corner_tests(int total) {
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
            return -1;
        }
        if (run_test(path, pos, apple, A, B)) {
            passed++;
        }
        fclose(path);
    }
    printf("Passed %d / %d corner tests.\n", passed, total);
    return passed;
}

int run_random_corner_tests(int total) {
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
            return -1;
        }
        if (run_test(path, pos, apple, A, B)) {
            passed++;
        }
        fclose(path);
    }
    printf("Passed %d / %d random corner tests.\n", passed, total);
    return passed;
}

int main() {
    int total = 0, passed = 0;
    int count = 100;
    passed += run_random_tests(10 * count);
    total += 10 * count;
    passed += run_random_square_tests(100);
    total += count;
    passed += run_square_tests(100);
    total += count;
    passed += run_random_edge_tests(count);
    total += count;
    passed += run_edge_tests(count);
    total += count;
    total += run_random_corner_tests(count);
    total += count;
    total += run_corner_tests(count);
    total += count;
    return 0;
}
