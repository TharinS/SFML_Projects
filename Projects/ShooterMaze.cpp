#include <stdlib.h>
#include <time.h>
#include <windows.h>

#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;
using namespace sf;


class Game {
public:
    //Constructors / Destructors 
    Game();
    virtual ~Game();
private:

}


int main() {
    RenderWindow window(VideoMode(800, 600), "Game", Style::Default);



    while (window.isOpen()) {
        Event Evnt;
        while (window.pollEvent(Evnt)) {
            switch (Evnt.type) {
                case Evnt.Closed:
                    window.close();
                    break;
                case Evnt.KeyPressed():
                    
                    break;
            }
        }
        window.clear();
        window.display();
    }
}