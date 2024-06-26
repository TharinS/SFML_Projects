#include <math.h>    // Header file for mathematical functions
#include <stdio.h>   // Header file for standard input/output functions
#include <stdlib.h>  // Header file for general purpose functions, including memory allocation and exit
#include <time.h>    // Header file for time-related functions

#include <SFML/Graphics.hpp>  // SFML library for graphics
#include <iostream>           // Header file for standard input/output streams

using namespace sf;   // Namespace for SFML library
using namespace std;  // Standard namespace

int main() {
    RenderWindow Window(VideoMode(800, 600), "DVD Logo", Style::Default);  // Create window with resolution of 800x600 and title of "DVD Logo"
    Window.setFramerateLimit(60);                                         // Set the frame rate limit to 120 frames per second

    // DVD Logo Sprite
    Texture DVDText;                                                                                           // Create a texture object for the DVD logo
    DVDText.loadFromFile("Projects/assets/DVDLogo.png");  // Load the texture from a file
    DVDText.setSmooth(true);                                                                                   // Set the texture to use smooth filtering
    Sprite DVDLogo;                                                                                            // Create a sprite object for the DVD logo
    DVDLogo.setTexture(DVDText);                                                                               // Set the texture of the sprite to the loaded DVD logo texture
    DVDLogo.setColor(Color::Blue);                                                                             // Set the color of the sprite to blue
    DVDLogo.setScale(Vector2f(0.50, 0.50));                                                                    // Scale the sprite down by a factor of 0.5
    float DirectionX = 2, DirectionY = 2;                                                                      // Set initial movement directions for the sprite
    DVDLogo.setOrigin(Vector2f(DVDLogo.getLocalBounds().width / 2, DVDLogo.getLocalBounds().height / 2));      // Set the origin of the sprite to its center

    while (Window.isOpen()) {                  // Loop until the window is closed
        DVDLogo.move(DirectionX, DirectionY);  // Move the DVD logo sprite in the x and y directions
        sf::Event EVNT;                        // Create an event object
        while (Window.pollEvent(EVNT)) {       // Poll for events
            switch (EVNT.type) {
                case EVNT.Closed:    // If the window is closed
                    Window.close();  // Close the window
                    break;
            }
        }

        if ((DVDLogo.getPosition().x >= 800) || (DVDLogo.getPosition().x <= 0)) {             // If the DVD logo sprite hits the left or right edge of the window
            DVDLogo.setColor(Color(rand() % 255, rand() % 255, rand() % 255, rand() % 255));  // Set the color of the sprite to a random color
            DVDLogo.move(DirectionX *= -1, 0);                                                // Reverse the x direction of movement
        }
        if ((DVDLogo.getPosition().y >= 600) || (DVDLogo.getPosition().y <= 0)) {             // If the DVD logo sprite hits the top or bottom edge of the window
            DVDLogo.setColor(Color(rand() % 255, rand() % 255, rand() % 255, rand() % 255));  // Set the color of the sprite to a random color
            DVDLogo.move(0, DirectionY *= -1);                                                // Reverse the y direction of movement
        }

        Window.clear();  // Clear the window
        Window.draw(DVDLogo);
        Window.display();
    }
}