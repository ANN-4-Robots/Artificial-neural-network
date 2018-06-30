#include <iostream>
#include <vector>
#include <cmath>
#include <SFML/Graphics.hpp>
#include "point.hpp"
#include "perceptron.hpp"


int main() {
    srand( time( NULL ) );
    sf::RenderWindow win ( sf::VideoMode( width, height ), "Perceptron");


    Perceptron pepe;

    // Create set of points which will be drawn on screen
    std::vector< TrainP > drawSet;
    for ( int i = 0; i < 2000; ++i )
        drawSet.emplace_back();

    // bool trained{};

    // Main loop
    while ( win.isOpen() ) {
        sf::Event event;

        // Proccess window events
        while ( win.pollEvent( event ) ) {
            if ( event.type == sf::Event::Closed )
                win.close();
            if ( event.type == sf::Event::KeyPressed ) {
                if ( event.key.code == sf::Keyboard::Escape ) {
                    // std::cout << "Escape pressed!" << std::endl;
                    win.close();
                }
            }
        }

        // Training until
        for ( int i = 0; i < 10000; ++i ) {
            TrainP trainP;                                  // Create random training point
            pepe.train( trainP.coords, trainP.isAbove );
        }

        // Color all points according to perceptron output
        for ( auto& point : drawSet ) {
            if ( pepe.think( point.coords ) >= 0.5 )
                point.color();
            else
                point.color( false );
        }

        // Manage window stuff 
        win.clear( sf::Color(51, 51, 51) );
        for ( auto& point : drawSet )
            point.draw(win);
        win.display();
    }
    return 0;
}
