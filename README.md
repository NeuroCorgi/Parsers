# Parsing

Project with simple parsering algorithms:
- Unger parser

## Building

Build the program with `cmake` in build directory and then make executable with `make`

```console
$ cd build
$ cmake ..
$ make
```

## Running

After calling the executable, it will ask you to input the expression in the `stdin` and then print the concrete syntax tree or `Not parsable by given grammar` to the `stdout`

```console
$ cd build
$ ./parsing
$ expr> 1+1
```
