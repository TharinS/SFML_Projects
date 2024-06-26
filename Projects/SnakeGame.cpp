#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;
using namespace std;

class Cell : public RectangleShape {
   public:
    int property = 0;   //0 - Empty | 1 - Snake | 2 - Food
    int direction = 3;  //0 - Up | 1 - Right | 2 - Down | 3 - Left
};

Vector2i newPos(int currentX, int currentY, int direction) {
    switch (direction) {
        case 0:
            return Vector2i(currentX, 1 + currentY);
            break;
        case 1:
            return Vector2i(1 + currentX, currentY);
            break;
        case 2:
            return Vector2i(currentX, 1 - currentY);
            break;
        case 3:
            return Vector2i(1 - currentX, currentY);
            break;
    }
    return Vector2i(currentX, currentY);
}

int main() {
    srand(static_cast<float>(rand()) / static_cast<float>(RAND_MAX));
    RenderWindow Window(VideoMode(800, 800), "Snake Game", Style::Default);
    Window.setFramerateLimit(60);

    Texture Assets;
    Assets.loadFromFile("C:\\Users\\thari\\Desktop\\Progamming_Stuff\\SFML\\Projects\\assets\\Packman.png");

    RectangleShape Box;
    Box.setFillColor(Color::White);
    Box.setSize(Vector2f(800,800));

    Sprite Character;
    Character.setTexture(Assets);
    Character.setScale(Vector2f(3,3));

    sf::Event EVNT;
    while (Window.isOpen()) {
        while (Window.pollEvent(EVNT)) {
            switch (EVNT.type) {
                case EVNT.Closed:
                    Window.close();
                    break;
            }
        }

        //Drawing
        Window.clear();
        Window.draw(Box);
        Window.draw(Character);
        Window.display();
    }
    return 0;
}