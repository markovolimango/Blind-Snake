# Snake

The solution to the Jetbrains internship task of "Blind Snake", in C

## Using the Application

### Prerequisites
- C version 23 or later
- CMake 3.29 or later

### Buidling the Project
- Clone the repository.
```bash
git clone https://github.com/markovolimango/snake
```
- Create a build directory and navigate to it.
```bash
cd JSON-Parser
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

### Running the expression evaluation
- Place your JSON file in the build directory.
- Run the *json_eval* executable and input the file name and expression.
```bash
./json_eval
[filename] [expression]
```
Examples:
```bash
./json_eval
test.json a.b[1]
```
```bash
./json_eval
test.json a.b[max(0,a.b[1])]
```
```bash
./json_eval
test.json a.b[3][1]+a.b[size(a)]
```

### Running the tests
- Just run the *tests* executable.
```bash
./tests
```
