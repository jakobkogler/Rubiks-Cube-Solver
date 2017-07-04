# Rubik's Cube Solver

An optimal solver for the Rubik's Cube implemented in C++. 

### Requirements:

 - C++11 compiler (gcc, clang, ...)
 - CMake >= 3.3
 - Boost >= 1.56

### Usage:

First clone the project and change to the project directory:

    git clone https://github.com/jakobkogler/Rubiks-Cube-Solver.git
    cd Rubiks-Cube-Solver

Compile the program and run it with

    mkdir build
    cd build
    cmake ..
    make
    ./Rubiks_Cube_Solver

At the moment there is no interactive mode. You need to specify scrambles in `main.cpp` and recompile.

### License

Copyright (C) 2017 Jakob Kogler, [MIT License](https://github.com/jakobkogler/Rubiks-Cube-Solver/blob/master/LICENCE.txt)
