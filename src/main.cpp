#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <cmath>
#include <fstream>
#include "matrix.hpp"
#include "point.hpp"
#include "neuralnet.hpp"
#include "idx.hpp"
#include "display.hpp"
#include "fpsClock.hpp"

using namespace std;
int main() {
    srand( time( NULL ) );

    sf::RenderWindow win ( sf::VideoMode( 800, 800 ), "Neural Net");
    Idx idx;
    int count{};
    

    while( win.isOpen() ) {

        // Process window events
        sf::Event event;
        while ( win.pollEvent( event ) ) {	
            if ( event.type == sf::Event::Closed ) win.close();	
            if ( event.type == sf::Event::KeyPressed ) {
                if ( event.key.code == sf::Keyboard::Escape ) win.close();	
                if ( event.key.code == sf::Keyboard::Space ) ++count;
            }	
        }
        Matrix <float> img = idx.getImage(count);
        Matrix <float> lbl = idx.getLabel(count);

        win.clear( sf::Color( 69, 69, 69 ) );
        drawImage( &win, img );
        drawText( &win, 10 , 300, "Current digit: " + to_string( int( lbl[0][0] )));
        drawOutput( &win, 500, 10, 20, img);
        win.display();
    }


    return 0;
}
