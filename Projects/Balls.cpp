#include <SFML/Graphics.hpp>

using namespace sf;

int main() {
    RenderWindow MainWindow(VideoMode(400, 400), "Ball Simulation", Style::Titlebar);
    
    Event SystemEvent;
    while (MainWindow.isOpen()) {
        MainWindow.clear();
        MainWindow.display();
    }
}