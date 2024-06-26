#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include <time.h>


int main(){
    sf::RenderWindow window(sf::VideoMode(1366,768),"Balls",sf::Style::Resize | sf::Style::Default);
    window.setFramerateLimit(60);
    const sf::Vector2f Center_Screen = sf::Vector2f((float)window.getSize().x/2,(float)window.getSize().y/2);
    //100 Tiny Circle's Jumping Sim 
    float x,y;
    int Size = 5;
    sf::CircleShape Ball[Size];
    float Vel_X[Size];
    float Vel_Y[Size];
    srand(time(NULL));
    for(int i = 0; i < Size; i++){
        Vel_X[i] = 10+rand()%20;
        Vel_Y[i] = 10+rand()%20;  
        Ball[i].setRadius(15.0f);
        // if(i%2 == 0){
        //     Ball[i].setFillColor(sf::Color::Red);
        // }
        // else if(i%3 == 0){
        //     Ball[i].setFillColor(sf::Color::Green);
        // }
        // else if(i%5 == 0){
        //     Ball[i].setFillColor(sf::Color::Blue);
        // }
        // else{
        //     Ball[i].setFillColor(sf::Color::Blue);
        // }
        Ball[i].setPosition((float)1+rand()%1300,(float)1+rand()%700);
    }
    while(window.isOpen()){
        sf::Event evnt;
        while(window.pollEvent(evnt)){
            switch(evnt.type){
                case evnt.Closed: window.close();break;
            }
        }
        for(int i = 0; i < Size; i++){
            if((Ball[i].getPosition().x == Center_Screen.x) && (Ball[i].getPosition().y == Center_Screen.y)){
                Vel_Y[i] *= (-1);
                Vel_X[i] *= (-1); 
            }
            if((Ball[i].getPosition().x > Center_Screen.x) && (Ball[i].getPosition().y < Center_Screen.y)){
                Vel_X[i] *= (-1); 
                Vel_Y[i] *= (-1);
            }
            if((Ball[i].getPosition().x < Center_Screen.x) && (Ball[i].getPosition().y > Center_Screen.y)){
                Vel_X[i] *= (-1); 
                Vel_Y[i] *= (-1);
            }
            Ball[i].move(Vel_X[i],Vel_Y[i]);
        }
        //Ball Collision Detection
        for(int i = 0; i < Size; i++){
            for(int j = 0; j < Size; j++){
                if(i != j){
                    if(Ball[i].getGlobalBounds().intersects(Ball[j].getGlobalBounds())){
                        sf::CircleShape Temp;
                        Temp.setFillColor(Ball[i].getFillColor());
                        Ball[i].setFillColor(Ball[j].getFillColor());
                        Ball[j].setFillColor(Temp.getFillColor());
                        Vel_X[j] *= (-1);
                        Vel_Y[j] *= (-1);
                        Ball[j].move( Vel_X[j],Vel_Y[j]);
                    }
                }
            }
        }
        //Border COllision Detection
        for(int i = 0; i < Size; i++){
            if(Ball[i].getPosition().x <= 0){
                Vel_X[i] *= (-1);
                Ball[i].move( Vel_X[i],Vel_Y[i]);
                }
            if(Ball[i].getPosition().y <= 0){
                Vel_Y[i] *= (-1);
                Ball[i].move( Vel_X[i],Vel_Y[i]);
            }
            if(Ball[i].getPosition().y + Ball[i].getLocalBounds().height >= window.getSize().y){
                Vel_Y[i] *= (-1);
                Ball[i].move( Vel_X[i],Vel_Y[i]);
            }
            if(Ball[i].getPosition().x + Ball[i].getLocalBounds().width >= window.getSize().x){
                Vel_X[i] *= (-1);
                Ball[i].move( Vel_X[i],Vel_Y[i]);
            }
        }
        window.clear();
        for(int i = 0; i < Size; i++){
            window.draw(Ball[i]);
        }
        window.display();
    }
    return 0;
}