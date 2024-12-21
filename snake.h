#ifndef SNAKE_H
#define SNAKE_H

typedef struct {
    int x;
    int y;
} Position;

bool send_signal(char signal, Position *pos, Position apple, int A, int B);

long long search(FILE *path, Position *pos, Position apple, int A, int B);

#endif
