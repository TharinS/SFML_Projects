#include <stdlib.h>  // General purpose functions, including memory allocation
#include <time.h>    // Functions to access the current date and time
#include <unistd.h>  // Provides access to the POSIX API

#include <SFML/Graphics.hpp>  // Declarations of the graphics module of SFML
#include <iostream>           // Standard input/output stream objects

using namespace sf;   // Using the SFML namespace
using namespace std;  // Using the standard namespace

// Define a class named Cell that inherits from the RectangleShape class of SFML
class Cell : public sf::RectangleShape {
   public:
    // Define two integer variables to represent the current and previous state of the cell
    // isAlive: represents the current state of the cell (1 for alive, 0 for dead)
    // preState: represents the previous state of the cell (1 for alive, 0 for dead)
    int isAlive = 0;
    int preState = 0;
};

// This function takes in the X and Y coordinates and the width of the array, and returns a key value representing the index of a cell
int ReturnKey(int X, int Y, int Width) {
    return X + Width * Y;
}

// This function takes in a key value and the width of the array, and returns the X and Y coordinates of a cell as a Vector2i
Vector2i ReturnCoordinates(int Key, int Width) {
    Vector2i Coordinates;
    Coordinates.x = Key % Width;
    Coordinates.y = Key / Width;
    return Coordinates;
}

// This function counts the number of living neighbors around a given cell in a 2D grid
int countNeighbours(vector<Cell> &Array, int x, int y, int width) {
    int Neighbours = 0;
    int cols, rows;
    int Key = ReturnKey(x, y, width);
    // Check the 8 surrounding cells of the current cell and count the number of living neighbors
    for (int i = -1; i < 2; i++) {
        for (int j = -1; j < 2; j++) {
            // Calculate the coordinates of the current neighbor
            cols = (x + i + 80) % 80;
            rows = (y + j + 80) % 80;
            // Get the key value of the current neighbor
            Key = ReturnKey(rows, cols, width);
            // If the neighbor is alive, increment the neighbor count
            if (Array[Key].preState == 1) {
                Neighbours++;
            }
        }
    }
    // If the current cell is alive, decrement the neighbor count
    Key = ReturnKey(x, y, width);
    if (Array[Key].preState == 1) {
        Neighbours--;
    }
    // Return the total number of living neighbors
    return Neighbours;
}

int main() {
    int Size = 100;
    // seed the random number generator
    srand(static_cast<float>(rand()) / static_cast<float>(RAND_MAX));
    // create a window to render the game
    RenderWindow Window(VideoMode(800, 800), "Conway's Game of Life", Style::Default);

    // create a vector of cells and initialize their positions, size and color
    vector<Cell> VecArray(Size * Size);
    int MasterKey;
    int X = 0;
    int Y = 0;
    for (int i = 0; i < Size; i++) {
        for (int j = 0; j < Size; j++) {
            MasterKey = ReturnKey(i, j, Size);
            // randomly set the initial state of each cell
            if (static_cast<float>(rand()) / static_cast<float>(RAND_MAX) < 0.5) {
                VecArray[MasterKey].isAlive = 1;
                VecArray[MasterKey].preState = 1;
            }
            VecArray[MasterKey].setPosition(Vector2f(X, Y));
            VecArray[MasterKey].setSize(Vector2f(8, 8));
            VecArray[MasterKey].setFillColor(Color::White);
            Y += 10;
        }
        Y = 0;
        X += 10;
    }

    int Neighbours;
    int N;
    int cols, rows;
    sf::Event EVNT;

    // game loop
    while (Window.isOpen()) {
        Window.clear();
        // for each cell in the vector
        for (int i = 0; i < Size; i++) {
            for (int j = 0; j < Size; j++) {
                MasterKey = ReturnKey(i, j, Size);

                // count the number of live neighbours
                Neighbours = 0;
                for (int x = -1; x < 2; x++) {
                    for (int y = -1; y < 2; y++) {
                        cols = (i + x + Size) % Size;
                        rows = (j + y + Size) % Size;
                        N = ReturnKey(cols, rows, Size);
                        if (VecArray[N].preState == 1) {
                            Neighbours++;
                        }
                    }
                }
                // decrement neighbour count for the current cell if it's alive
                if (VecArray[MasterKey].preState == 1) {
                    Neighbours--;
                }

                // apply the game of life rules to determine the new state of the cell
                if (VecArray[MasterKey].isAlive == 0 && Neighbours == 3) {
                    VecArray[MasterKey].isAlive = 1;
                } else if ((VecArray[MasterKey].isAlive == 1) && (Neighbours <= 1)) {
                    VecArray[MasterKey].isAlive = 0;
                } else if (VecArray[MasterKey].isAlive == 1 && Neighbours >= 4) {
                    VecArray[MasterKey].isAlive = 0;
                } else if (VecArray[MasterKey].isAlive == 1 && (Neighbours == 2 || Neighbours == 3)) {
                    VecArray[MasterKey].isAlive = 1;
                }
            }
        }

        for (int i = 0; i < Size; i++) {
            for (int j = 0; j < Size; j++) {
                MasterKey = ReturnKey(i, j, Size);
                if (VecArray[MasterKey].isAlive == 1) {
                    VecArray[MasterKey].setFillColor(Color::Yellow);
                } else {
                    VecArray[MasterKey].setFillColor(Color::Black);
                }
                VecArray[MasterKey].preState = VecArray[MasterKey].isAlive;
                Window.draw(VecArray[MasterKey]);
            }
        }
        Window.display();

        while (Window.pollEvent(EVNT)) {
            switch (EVNT.type) {
                case EVNT.Closed:
                    Window.close();
                    break;
            }
        }
    }
}
