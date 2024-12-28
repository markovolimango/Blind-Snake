#ifndef SNAKE_H
#define SNAKE_H

typedef struct {
    int x;
    int y;
} Position;

//the move function
bool send_signal(char signal, Position *pos, Position apple, int A, int B);

//the function that follows the defined path and tries to find the apple
long long find_apple(FILE *path, Position *pos, Position apple, int A, int B);

#endif
