#include <SFML/Graphics.hpp>
#include <cmath>
#include <fstream>
#include <iostream>

using namespace std;
using namespace sf;

#define MAX_VERTICES 30
#define RES_x 800
#define RES_y 800

void importVectors(Vector2f *Arr, string Location) {
    std::ifstream File(Location, std::ifstream::in);

    if (!File.good()) {
        cout << "could not open" << endl;
        return;
    }

    string Chars, temp;
    int i = 0;

    while (!File.eof()) {
        getline(File, temp, '\n');

        string x, y;
        if (temp.size() > 0) {
            x = temp.substr(0, temp.find(' '));
            y = temp.substr(temp.find(' '), temp.size() - 1);

            (Arr + i)->x = stoi(x);
            (Arr + i)->y = stoi(y);

            i++;
        }
    }

    File.close();
}

void coordinateTopositon(Vector2f *Arr, CircleShape *Objs, int WindowX, int WindowY) {
    Vector2f Midpoint = Vector2f((WindowX / 2) - 1, (WindowY / 2) - 1);
    Vector2f Position;

    for (int i = 0; i < MAX_VERTICES; i++) {
        Position.x = Midpoint.x + (Arr + i)->x;
        Position.y = Midpoint.y + (Arr + i)->y;

        (Objs + i)->setPosition(Position);
    }
}

void scaleCoordinates(Vector2f *Arr, float scaleFactor) {
    for (int i = 0; i < MAX_VERTICES; i++) {
        (Arr + i)->x = (Arr + i)->x * scaleFactor;
        (Arr + i)->y = (Arr + i)->y * scaleFactor;
    }
}

void scaleCorrdinates(Vector2f *Arr, float scaleFactorX, float scaleFactorY) {
    for (int i = 0; i < MAX_VERTICES; i++) {
        (Arr + i)->x = (Arr + i)->x * scaleFactorX;
        (Arr + i)->y = (Arr + i)->y * scaleFactorY;
    }
}

void rotateVectors(Vector2f *Arr, float rotateDegree) {
}

void printArr(Vector2f *Arr) {
    for (size_t i = 0; i < MAX_VERTICES; i++) {
        cout << "x - " << (Arr + i)->x << ", y - " << (Arr + i)->y << endl;
    }
}

int main() {
    Vector2f Arr[MAX_VERTICES];
    CircleShape Vertex[MAX_VERTICES];

    for (int i = 0; i < MAX_VERTICES; i++) {
        Vertex[i].setFillColor(Color::White);
        Vertex[i].setRadius(2);
        Vertex[i].setPosition(Vector2f(0, 0));
    }

    importVectors(Arr, "Data\\Vector.txt");

    scaleCoordinates(Arr, 50.0);

    coordinateTopositon(Arr, Vertex, RES_x, RES_y);

    RenderWindow Window(VideoMode(RES_x, RES_y), "Polygon Generator", Style::Default);
    Event evnt;

    printArr(Arr);

    // Main Loop
    while (Window.isOpen()) {
        while (Window.pollEvent(evnt)) {
            switch (evnt.type) {
                case evnt.Closed:
                    Window.close();
                    break;
            }
        }

        Window.clear();
        for (int i = 0; i < MAX_VERTICES; i++) {
            Window.draw(Vertex[i]);
        }
        Window.display();
    }
    return 0;
}