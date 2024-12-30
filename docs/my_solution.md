# My solution to "Blind Snake"

## Some observations

Since there is no way to see the apple, the only way to always find it is to visit every square where it could be, which
is every square of every possible screen size.

Because hitting the edge of the screen teleports the snake to the other edge, we can treat the playing field as
infinite, with the apple also repeating infinitely.

Since the playing field is infinite, we can always say that the starting position is (1, 1), and adjust everything else
accordingly.

## The idea

Let's say we know *S* and start at (1, 1). Every possibility for the screen size is a rectangle *A* x (*S* / *A*) where
*A* has to be a divisor of *S*. So, in order to cover every possible field for the screen size *S*, we just need to go
through all of those rectangles. If we write the dimensions of the rectangles as a function *f*(*A*) = *B*, it would be
a subset of the function *f*(*x*) = *S* / *x*, where *x* is a divisor of *S*. For example, here are all the
possibilities for *S* = 25, and the line *y* = 25 / *x*. The rectangles are 1 x 25, 5 x 5 and 25 x 1.

![Example for S = 25](images/img1.png)

Now let's do the same thing (draw every possible screen size) for every *S* < 25, and add those rectangles to this
image.

![Example for S = 25](images/img2.png)

We can see that in order to cover every possible square for *S* <= 25, we just need to move under the line *y* = 25 /
*x*. This makes sense, because for every *S1* < *S* and every *x*, *S1* / *x* < *S* / *x*, so by going under *y* = *S* /
*x* we automatically go under every line *y* = *S1* / *x*.\
Now the assumption is, that if we just cover every square under *y* = 1,000,000 / *x*, we will cover every possible
square where the apple could be.

### Proof

Firstly, let's define what it means for a square to be under the line: The square (*x*, *y*) is under the line if *y* <=
1,000,000 / *x*. We can rewrite that as *x* * *y* <= 1,000,000, which is exactly what we need. We start at (1, 1) and
visit every square that forms a rectangle whose area is less than or equal to 1,000,000.

This proves that one of these squares has to contain the apple and that it is the smallest set of squares possible, that
has to contain the apple, because there's no square where *x* * *y* > 1,000,000. So the amount of squares we need to
visit is around *S* * ln(*S*) (where *S* = 1,000,000), which is the definite integral of *S* / *x* from *x* = 1 to *x* =
*S*.

## Generating the path

I decided that, since the snake is going to be taking the same path every time, I would generate that path first, and
then, when playing the game or running the tests, the snake would just follow the already generated path. So the path is
stored in a .txt file, where moves are written as one character representing the direction, and then a number
representing the amount of times the snake should move in that direction.

### One curve

My first idea was to just go under the line *y* = 1,000,000 / *x* once, so not visit all squares but just those on the
edge and then remember that path. It wouldn't be directly written into the .txt file, but just remembered. My goal is
then to start from (1, 1) and make bigger and bigger curves, slowly reaching the biggest one what I remembered. I
accomplished this by storing those first moves in an array and using two pointers that start in the middle of said
array. I would then write the part between those pointers to the file, and move them towards the edges of the array,
while flipping the direction of the path every time. In this example image it's clear why this works, as every curve is
the same as it's next bigger curve, but without the first and last two groups of moves. By group of moves I mean all
moves that are in the same direction.

![Example illustration](images/img3.png)

This seemed to work great, reaching (1, 1,000,000) and (1,000,000, 1) in around 14 million moves. But the problem is
that while the path it takes to these extremes is optimal, the path it takes to, say, (1, 10,000) is not. Because to get
to that point it won't be following an exponential curve, but just a small part of one, which is closer to just a
straight line. So the amount of moves it took to get to there was a lot more than 350,000.

### Multiple curves

So, in order to optimize it I decided to slice it up into multiple sections. I ran a lot of tests and observed which
ones usually failed. After some tweaking and adjusting I ended up with the numbers in the code right now (2,916, 50,176,
320,356 and 1,000,000). They had to be squares of whole numbers, in order for the path generation algorithm to work
nicely and always start from (1, 1). So the algorithm would first make the path for *S* <= 2,916, and end up at (1,
2,916). This would efficiently find the path to all of those squares, because the losses I talked about in the last
paragraph didn't get to grow too big. Then it would generate the path for *S* <= 50,176, but starting from (1, 2,916)
instead of (1, 1). This isn't a problem, because as we already said, we can assume any starting point is (1, 1), as long
as we complete the full path. This works well because the area we covered under *y* = 2,916 / *x* is relatively small
compared to the area under *y* = 50,176 / *x*. Then it would just repeat the process for the two remaining numbers.

This improved success rates greatly, but it still faced problems with squared that were just a little bit to the right
of one of the numbers I set, like for example (3,000, 1). It took a lot of moves to get there, because after completing
the path for *S* <= 2,916, it would start slowly moving right again from *x* = 1, and often that would be too slow.

![Example illustration](images/img4.png)

This illustration is not representative of actual values, because it wouldn't be readable, but you can see why it
struggled with those squares. What is important to mention is that the actual numbers are adjusted so that the algorithm
really always ends up at the top and not the side. It can be proven that that's true for all squares of even numbers,
but for this use it's enough to just see where the algorithm ends up in these three cases.

### Further optimization

The change that fixed a lot of these issues was pretty simple: I just flipped every other "shape". So far I treated the
rectangles as going right and up from the start, but the solution would be just as valid if we looked at rectangles
going left and up from the start (or left/right and down). So now this is an illustration showing approximately what
this path looks like:

![Example illustration](images/img5.png)

This improves the algorithm greatly, because now the squares that used to be problematic are covered really quickly,
because after the first section the snake is at (1, 2,916) and moves left. If we remember that reaching an edge
teleports the snake to the other side, we can see that this path covers the furthest right squares (which used to be
problematic) immediately after completing the first section. This solution still encounters some problems, as there are
still a few squares that can take a bit too many moves to reach.

Reminder: The actual starting position doesn't have to be (1, 1) and moving left from there doesn't have to move the
snake to the other edge, but we can treat it as such, as noted in the beginning.

## The stats

Even though every now and then this solution still takes too many steps to find the apple, it still finds it every time
and does so in the correct amount of moves the very vast majority of the time.

I ran seven different types of tests: random tests, where every input value in randomized; random square tests, where
*A* = *B* and everything else is random; square corner tests, where *A* = *B*, *x_start* = *y_start* = 1 and *x_apple* =
*y_apple* = *A* (= *B*), but *S* is random; random edge tests, where either *A* or *B* is 1 and everything else is
random; edge corner tests, where either *A* or *B* is 1, *x_start* = *y_start* = 1 and the apple is on the other side of
the rectangle, but *S* is random; random corner tests, where *x_start* = *y_start* = 1 and everything else is random;
and finally just corner tests, where *x_start* = *y_start* = 1, *x_apple* = *A*, *y_apple* = *B* and *A* and *B* are
random.

From all my testing (hundreds of thousands of tests), I've never had one random tests, random square test, square corner
test or random corner test fail. I know they don't have a 100% success rate, but that's what happened in my testing. The
corner tests had a 99,99% success rate, the random edge tests 99,86% and the edge corner tests 98,78%.

## Ideas for further improvement

Sadly, I saw this task only about ten days before the application end date, so I didn't have the time to implement and
test some other ideas I had, but I will try them after the time is up, because I think this was a really fun challenge
and I just want to get to that 100% for me. The main problem I couldn't fully implement was an algorithm that goes
between two curves, repeating as few squares as possible, while also visiting the edges often enough. With an algorithm
like that I think my solution would be complete, because even now the snake never takes a lot more than 35 * *S* moves,
but just slightly goes over. Maybe such an algorithm isn't possible between these curves by which I split my path, but
if I tried out some numbers that followed a rule it could be simpler.