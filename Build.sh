#!/bin/bash

# Compile the source code into an object file
g++ -c Projects/BouncingDVD.cpp -o Main.o

# Link the object file with the SFML libraries to create the executable
g++ Main.o -o BouncingDVD -lsfml-graphics -lsfml-window -lsfml-system

# Run the executable
./BouncingDVD
