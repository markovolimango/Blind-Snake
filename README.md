# Snake

My solution of the JetBrains internship task of "Blind Snake", in C

The task formulation can be found in "task.md"

## Solution explanation

The explanation of what my solution is and why it works is in the my_solution.md file, in the docs folder.

## Using the Application

### Prerequisites

- C version 23 or later
- CMake 3.29 or later

### Buidling the Project

- Clone the repository.

```bash
git clone https://github.com/markovolimango/Blind-Snake
```

- Create a build directory and navigate to it.

```bash
cd Blind-Snake/src
mkdir build
cd build
```

- Generate the build files using CMake.

```bash
cmake ..
```

- Build the project.

```bash
make
```

### Generating the path

- Since the path the "snake" takes is always the same, it is generated before playing or running the tests.
- Just run the *generate_path* executable.

```bash
./generate_path
```

### Playing the game

- Run the *play* executable and input the conditions in the given order.

```bash
./play
[A] [B] [x_start] [y_start] [x_apple] [y_apple]
```

### Running the tests

- Run the *tests* executable and input the number of tests you want per category.
- If you input a number *n*, the application will run *10n* random tests, then *n* tests in each category.

```bash
./tests
[n]
```
