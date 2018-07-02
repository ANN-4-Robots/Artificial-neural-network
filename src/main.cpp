#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <cmath>
#include "matrix.hpp"
#include "point.hpp"
#include "neuralnet.hpp"
#include "fpsClock.hpp"


int main() {
    srand( time( NULL ) );
    fpsClock clock(60);
    sf::RenderWindow win ( sf::VideoMode( width, height ), "Neural Net");

    NeuralNet nn( 2, 1, 1 );
    try {
        std::vector< TrainP > drawSet;
        for ( int i = 0; i < 2000; ++i )
            drawSet.emplace_back();

        while ( win.isOpen() ) {
            if ( clock.tick() ) {
                sf::Event event;
                while ( win.pollEvent( event ) ) {
                    if( event.type == sf::Event::Closed )
                        win.close();
                }

                // Training untill
                for ( int i = 0; i < 1; ++i ) {
                    TrainP trainP;
                    nn.train( trainP.coords, Matrix<float>( {{ float(trainP.isAbove) }} ) );
                }

                for ( auto& point : drawSet ) {
                    if ( nn.feedforward( point.coords )[0][0] >= 0.5 )
                        point.color();
                    else
                        point.color( false );
                }

                win.clear( sf::Color(51, 51, 51) );
                for ( auto& point : drawSet )
                    point.draw(win);
                win.display();
            }
        }
        return 0;
    } catch ( const char* message ) {
        std::cout << message << std::endl;
    }
}
