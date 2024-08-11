## A simplified console implementation of the game "Life", invented by the English mathematician John Conway in 1970.

# C++ Standard Library:
#include <iostream>: Used to deal with input and output (eg std::cin, std::cout).
#include <cstdlib> and #include <stdlib.h>: These header files contain C standard library functions such as rand() and system(). Although both files contain similar functions, cstdlib is part of C++ and is recommended for use in C++ programs.

# Memory management features:
new and delete[]: Used to dynamically allocate and free memory for two-dimensional arrays (char** maps) that represent the game map.

# System calls:
#include <unistd.h>: Used for calls to system functions such as sleep() that pause program execution for a specified number of seconds.

# Loops and conditional statements:
For and do-while loops are used to iterate through arrays and perform game steps until the game ends.
Conditional statements if, else if, and else are used to test various conditions during the game.

# Working with two-dimensional arrays:
Basic operations in the game are performed on two-dimensional arrays that represent the game map. Operations include creating a map, copying data between maps, displaying the map on the screen, and changing the state of cells on the map.

# "Game of Life" mechanism:
The game logic is implemented based on the cellular automaton "Game of Life" (Conway's Game of Life), where cells can be "live" (*) or "dead" (-), and their state is updated depending on the number of neighbors.

# System commands for clearing the screen:
Uses the \x1B[2J\x1B[H escape code sequences to clear the screen in the console, allowing the map display to be updated on screen with each step of the game.
