# My solution to "Blind Snake"

Marko Popadić

## Some assumptions

1. Since there is no way to see the apple, the only way to always find it is to visit every square where it could be,
   which is every square of every possible screen size.
2. Because hitting the edge of the screen teleports the snake to the other edge, we can treat the playing field as
   infinite, with the apple repeating infinitely.
3. Since the playing field is infinite, we can always say that the starting position is (1, 1).

## The idea

Let's say we know *S* and start at (1, 1). Every possibility for the screen size is a rectangle *A* x (*S* / *A*) where
*A* has to be a divisor of *S*. So, in order to cover every possible field for the screen size *S*, we just need to go
through all of those rectangles.\
If we write the dimensions of the rectangles as a function *f*(*A*) = *B*, it would be a subset of the function *f*(*x*)
= *S* / *x*, where *x* is a divisor of *S*. For example, here are all the possibilities for *S* = 25, and the line *y* =
25 / *x*.\
![Example for S = 25](/images/img1.png)\
Now let's do the same thing for every *S* < 25, and add those rectangles to this image.
![Example for S = 25](/images/img2.png)\
We can see that in order to cover every possible square for *S* <= 25, we just need to move under the graph *y* = 25 /
*x*. This makes sense, because for every *S1* < *S* and every *x*, *S1* / *x* < *S* / *x*, so by going under *y* = *S* /
*x* we automatically go under every line *y* = *S1* / *x*.\
Now the assumption is, that if we just cover every square under *y* = 1,000,000 / *x*, we will cover every possible
square where the apple could be.

### Proof

Firstly, let's define what it means for a square to be under the line: The square (*x*, *y*) is under the line if *y* <=
1,000,000 / *x*. We can rewrite that as *x* * *y* <= 1,000,000, which is exactly what we need. We start at (1, 1) and
visit every square that forms a rectangle whose area is less than or equal to 1,000,000. This proves that one of these
squares has to contain the apple and that it is the smallest set of squares possible, that has to contain the apple
(because there's no repeating of rectangles).

## Generating the path

I decided that, since the snake is going to be taking the same path every time, I would generate that path first, and
then when playing the game or running the tests, the snake would just follow the already generated path.