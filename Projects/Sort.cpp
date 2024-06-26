#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;
using namespace std;

int main() {
    srand(time(NULL));
    RenderWindow Window(VideoMode(800, 600), "Sorting Demonstration", Style::Default);
    Window.setFramerateLimit(120);

    int size = 125;
    int T = 0;
    //Ints that will iterate over the list of boxes and be used for comparing
    int x = 0, y = x;
    RectangleShape Box[size];
    for (int i = 0; i < size; i++) {
        Box[i].setFillColor(Color::White);
        Box[i].setSize(Vector2f(7, 10 + rand() % 500));
        Box[i].setPosition(Vector2f(T, 0));
        T += 8;
    }

    while (Window.isOpen()) {
        for (int i = 0; i < size; i++) {
            Box[i].setFillColor(Color::Red);
            for (int j = i; j < size; j++) {
                sf::sleep(sf::milliseconds(10));
                Box[j].setFillColor(Color::Yellow);
            }
        }

        sf::Event EVNT;
        while (Window.pollEvent(EVNT)) {
            switch (EVNT.type) {
                case EVNT.Closed:
                    Window.close();
                    break;
            }
        }
        Window.clear(Color::Black);
        for (int i = 0; i < size; i++) {
            Window.draw(Box[i]);
        }
        Window.display();
    }
}