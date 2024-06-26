#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;

bool PlayerOutofBounds(float PlayerPos, float ScreenBounds) {
    if ((PlayerPos > ScreenBounds) || (PlayerPos < 0)) {
        return false;
    } else {
        return true;
    }
}

bool Player_AI_Path(sf::Vector2f Momentum, sf::Vector2f Position) {
    while (true) {
        if ((Position.x = 20) && ((Position.y <= 600) && (Position.y >= 0))) {
            return true;
        } else {
            Position.x += Momentum.x;
            Position.y += Momentum.y;
        }
    }
}

sf::Vector2f Player_AI_Pos(sf::Vector2f Momentum, sf::Vector2f Position) {
    while (true) {
        if ((Position.x = 20) && ((Position.y <= 600) && (Position.y >= 0))) {
            return Position;
        } else {
            Position.x += Momentum.x;
            Position.y += Momentum.y;
        }
    }
}

bool AI_Path(sf::Vector2f Momentum, sf::Vector2f Position) {
    while (true) {
        if ((Position.x = 780) && ((Position.y <= 600) && (Position.y >= 0))) {
            return true;
        } else {
            Position.x += Momentum.x;
            Position.y += Momentum.y;
        }
    }
    return false;
}

sf::Vector2f AI_Pos(sf::Vector2f Momentum, sf::Vector2f Position) {
    while (true) {
        if ((Position.x = 780) && ((Position.y <= 600) && (Position.y >= 0))) {
            return Position;
        } else {
            Position.x += Momentum.x;
            Position.y += Momentum.y;
        }
    }
}

int main() {
    srand(time(NULL));

    sf::RenderWindow Window(sf::VideoMode(800, 600), "Ping Pong", sf::Style::Default | sf::Style::Resize);
    Window.setFramerateLimit(60);

    // Background Sprite
    sf::Texture Background;
    Background.loadFromFile("Projects/assets/PPBackGround.png");

    sf::Sprite BackgroundSprite;
    BackgroundSprite.setTexture(Background);
    BackgroundSprite.setPosition(sf::Vector2f(0, 0));

    // Player Paddle Sprite
    sf::RectangleShape PlayerPaddle;
    PlayerPaddle.setPosition(sf::Vector2f(20, 50 + rand() % 500));
    PlayerPaddle.setSize(sf::Vector2f(10, 50));
    PlayerPaddle.setFillColor(sf::Color::White);
    PlayerPaddle.setOrigin(sf::Vector2f(5, 25));

    // AI Paddle Sprite
    sf::RectangleShape AIPaddle;
    AIPaddle.setPosition(sf::Vector2f(780, 50 + rand() % 500));
    AIPaddle.setSize(sf::Vector2f(10, 50));
    AIPaddle.setFillColor(sf::Color::White);
    AIPaddle.setOrigin(sf::Vector2f(5, 25));

    // Ball
    sf::CircleShape Ball;
    Ball.setRadius(10);
    Ball.setPosition(sf::Vector2f(400, 300));
    Ball.setOrigin(sf::Vector2f(5, 5));
    //
    float DirectionX = 5, DirectionY = 5;

    // Hit Boxes for the Walls
    sf::RectangleShape Wall[2];
    for (int i = 0; i < 2; i++) {
        Wall[i].setFillColor(sf::Color::Red);
        Wall[i].setSize(sf::Vector2f(7, 600));
    }
    Wall[0].setPosition(sf::Vector2f(0, 0));
    Wall[1].setPosition(sf::Vector2f(793, 0));

    sf::Clock DClock;

    while (Window.isOpen()) {
        // Window.clear();
        // Drawing Background
        Window.draw(BackgroundSprite);
        sf::Event EVNT;
        while (Window.pollEvent(EVNT)) {
            switch (EVNT.type) {
                case EVNT.Closed:
                    Window.close();
                    break;
            }
        }

        sf::Time deltaTime = DClock.restart();

        // KeyBoard Input
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            if (PlayerOutofBounds(PlayerPaddle.getPosition().y - 20.0, Window.getSize().y)) {
                PlayerPaddle.move(sf::Vector2f(0, -20.0));
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            if (PlayerOutofBounds(PlayerPaddle.getPosition().y + 20.0, Window.getSize().y)) {
                PlayerPaddle.move(sf::Vector2f(0, 20.0));
            }
        }

        // Ball Movement
        Ball.move(sf::Vector2f(DirectionX, DirectionY));
        // Ball and Wall Collision Code
        if ((Ball.getPosition().x >= 800)) {
            Ball.move(sf::Vector2f(DirectionX *= -1, 0));
        }
        if ((Ball.getPosition().y >= 600)) {
            Ball.move(sf::Vector2f(0, DirectionY *= -1));
        }
        if ((Ball.getPosition().x <= 0)) {
            Ball.move(sf::Vector2f(DirectionX *= -1, 0));
        }
        if ((Ball.getPosition().y <= 0)) {
            Ball.move(sf::Vector2f(0, DirectionY *= -1));
        }
        // Ball and Player Collision Code
        if (Ball.getGlobalBounds().intersects(PlayerPaddle.getGlobalBounds())) {
            Ball.move(sf::Vector2f(DirectionX *= -1, DirectionY *= 1));
        }
        // Ball and EndZone Collision Code
        if ((Ball.getGlobalBounds().intersects(Wall[0].getGlobalBounds())) || (Ball.getGlobalBounds().intersects(Wall[1].getGlobalBounds()))) {
            DirectionY = 0, DirectionX = 0;
            Window.close();
            cout << "Ball Hit" << endl;
        }
        // Ball and AI Collision Code
        if (AI_Path(sf::Vector2f(DirectionX, DirectionY), Ball.getPosition())) {
            AIPaddle.setPosition(AI_Pos(sf::Vector2f(DirectionX, DirectionY), Ball.getPosition()));
            if (Ball.getGlobalBounds().intersects(AIPaddle.getGlobalBounds())) {
                Ball.move(sf::Vector2f(DirectionX *= -1, DirectionY *= 1));
            }
        }

        // //Player AI Movement Uncomment the code below then compile to see AI vs AI
        // if (Player_AI_Path(sf::Vector2f(DirectionX, DirectionY), Ball.getPosition())) {
        //     PlayerPaddle.setPosition(Player_AI_Pos(sf::Vector2f(DirectionX, DirectionY), Ball.getPosition()));
        //     if (Ball.getGlobalBounds().intersects(PlayerPaddle.getGlobalBounds())) {
        //         Ball.move(sf::Vector2f(DirectionX *= -1, DirectionY *= 1));
        //     }
        // }

        // Player Sprite
        Window.draw(PlayerPaddle);
        Window.draw(Ball);
        Window.draw(AIPaddle);
        for (int i = 0; i < 2; i++) {
            Window.draw(Wall[i]);
        }
        Window.display();
    }
}