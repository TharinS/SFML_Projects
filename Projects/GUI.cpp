#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;
using namespace sf;

struct Button {
    sf::Vector2f ButtonDimensions;
    sf::Vector2f ButtonPosition;
    sf::RectangleShape Button;
};

typedef struct Button Button;

int main() {
    RenderWindow Window(VideoMode(800, 600), "GUI", Style::Default);

    Button Click;
    Click.ButtonDimensions.x = 100, Click.ButtonDimensions.y = 100;
    Click.Button.setSize(Click.ButtonDimensions);
    Click.ButtonPosition.x = 0, Click.ButtonPosition.y = 0;
    Click.Button.setPosition(Click.ButtonPosition);
    Click.Button.setOutlineColor(Color::White);
    Click.Button.setOutlineThickness(5);

    while (Window.isOpen()) {
        Event EVNT;
        while (Window.pollEvent(EVNT)) {
            switch (EVNT.type) {
                case EVNT.Closed:
                    Window.close();
                    break;
            }

            Window.clear();
            Window.draw(Click.Button);
            Window.display();
        }
    }
}