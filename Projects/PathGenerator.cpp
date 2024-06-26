#include <math.h>
#include <stdio.h>

#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;
using namespace std;

// class BoundingBox : public RectangleShape {
//     /* Dimensions */
//     int lenght = 0; /* Lenght of the bounding box */
//     int height = 0; /* Height of the bounding box */
//     int xCoord = 0; /* x coordinate of the bounding box */
//     int yCoord = 0; /* y coordinate of the bounding box */

//     /* States of the bounding box */
//     bool isMouseHovering = false;
//     bool isClicked = false;

//     /* Border Settings */
//     Color borderColor = Color::Green; /* Default Color is set to Green */
//     int borderThicc = 10;             /* Default border thiccness is set to 10px */

//     void setBoundSize(int Lenght, int Height, int XCoord, int YCoord) {
//         lenght = Lenght;
//         height = Height;
//         xCoord = XCoord;
//         yCoord = YCoord;
//     }
// };

class Point : public CircleShape {
   public:
    int pointType = 0;  //0 - Empty Type | 1 - Starting Point | 2 - Ending Point | 3 - Regular Point
};

float returnPos(int A) {
    return A * (-1);
}

float returnOpposite(int A, int B) {
    int C = A - B;
    if (C < 0) {
        C = returnPos(C);
    }
    return C;
}

float returnAdjacent(int A, int B) {
    int C = A - B;
    if (C < 0) {
        C = returnPos(C);
    }
    return C;
}

/* Returns the length of the line (Hypotenuse) */
float returnHypotenuse(float startPointX, float startPointY, float endPointX, float endPointY) {
    float A = startPointX - endPointX;
    if (A < 0) {
        A = returnPos(A);
    }
    float B = startPointY - endPointY;
    if (B < 0) {
        B = returnPos(B);
    }
    return sqrtf(((A * A) + (B * B)));
}

float returnAngle(float Opposite, float Hypotenuse) {
    return asinf(Opposite / Hypotenuse) * (180 / 3.141592654);
}

int main() {
    RenderWindow MainWindow(VideoMode(800, 800), "Path Generation", Style::Close);
    RectangleShape Line;
    int maxPoints = 256;
    int pointCounter = 0;
    bool startSet = false;
    bool endSet = false;
    Point Points[maxPoints];
    for (int i = 0; i < maxPoints; i++) {
        Points[i].setRadius(5.0);
    }

    Event windowEvent;
    while (MainWindow.isOpen()) {
        while (MainWindow.pollEvent(windowEvent)) {
            switch (windowEvent.type) {
                case Event::Closed:
                    MainWindow.close();
                    break;
                case Event::MouseButtonPressed:
                    if (Keyboard::isKeyPressed(Keyboard::LShift)) {
                        if (!startSet) {
                            Points[pointCounter].setFillColor(Color::Yellow);
                            Points[pointCounter].pointType = 1;
                            Points[pointCounter].setPosition(Vector2f(Mouse::getPosition(MainWindow).x, Mouse::getPosition(MainWindow).y));
                            startSet = true;
                            ++pointCounter;
                            break;
                        }
                        if (!endSet && startSet) {
                            Points[pointCounter].setFillColor(Color::Red);
                            Points[pointCounter].pointType = 2;
                            Points[pointCounter].setPosition(Vector2f(Mouse::getPosition(MainWindow).x, Mouse::getPosition(MainWindow).y));
                            endSet = true;
                            ++pointCounter;
                        }
                    } else {
                        //Spawning new point
                        Points[pointCounter].pointType = 3;
                        Points[pointCounter].setFillColor(Color::Green);
                        Points[pointCounter].setPosition(Vector2f(Mouse::getPosition(MainWindow).x, Mouse::getPosition(MainWindow).y));
                        ++pointCounter;
                    }
                    break;
            }
        }

        //Clears all points
        if (Keyboard::isKeyPressed(Keyboard::Q)) {
            for (int i = 0; i < pointCounter; i++) {
                Points[i].pointType = 0;
                Points[i].setFillColor(Color::Black);
            }
            startSet = false;
            endSet = false;
            pointCounter = 0;
        }

        if (Keyboard::isKeyPressed(Keyboard::Escape)) {
            MainWindow.close();
        }

        if (Keyboard::isKeyPressed(Keyboard::P)) {
            Line.setSize(Vector2f(returnHypotenuse(Points[0].getPosition().x, Points[0].getPosition().y, Points[1].getPosition().x, Points[1].getPosition().y), 5.0));
            Line.setPosition(Vector2f(Points[0].getPosition().x, Points[0].getPosition().y));
            Line.setFillColor(Color::White);
            Line.setRotation(returnAngle(returnOpposite(Points[0].getPosition().y, Points[1].getPosition().y), returnHypotenuse(Points[0].getPosition().x, Points[0].getPosition().y, Points[1].getPosition().x, Points[1].getPosition().y)));
        }

        MainWindow.clear();
        for (int i = 0; i < pointCounter; i++) {
            MainWindow.draw(Points[i]);
            MainWindow.draw(Line);
        }
        MainWindow.display();
    }
    return 0;
}