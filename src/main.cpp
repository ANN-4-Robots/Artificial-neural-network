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
    fpsClock clock(1);
    sf::RenderWindow win ( sf::VideoMode( width, height ), "Neural Net");

    NeuralNet nn( 2, 5, 1 );

// XOR ----------------------------------------------------------------------
    // std::vector<Matrix<float>> trainSet;
    // std::vector<Matrix<float>> ideal;
    // for ( auto i : { 0, 1 } ) {
    //     for ( auto j : { 0, 1 } ) {
    //         trainSet.push_back( Matrix<float>( {{(float)i},{(float)j}} ) );
    //         if ( i == j )
    //             ideal.push_back( Matrix<float>( {{0}} ));
    //         else
    //             ideal.push_back( Matrix<float>( {{1}} ));
    //     }
    // }

    // nn.setLearnRate(0.2);
    // long long i = 500000;
    // while (--i) {
    //     int random = rand()%4;
    //     nn.backpropagate( trainSet[random], ideal[random] );
    // }
    // for ( int i = 0; i < 4; ++i)
    //     std::cout << nn.feedforward( trainSet[i] );
//------------------------------------------------------------------------------

    try {
        std::vector< TrainP > drawSet;
        for ( int i = 0; i < 2000; ++i )
            drawSet.emplace_back();
        // for ( int j = 0; j < 50; ++j ) {
        //     for ( int i = 0; i < 10000; ++i ) {
        //         TrainP trainP;
        //         nn.backpropagate( trainP.coords, trainP.isAbove );
        //     }
        //     std::cout << j << std::endl;
        // }
        while ( win.isOpen() ) {
            if ( clock.tick() ) {
                sf::Event event;
                while ( win.pollEvent( event ) ) {
                    if( event.type == sf::Event::Closed )
                        win.close();
                }

                // Training untill
                for ( int i = 0; i < 10; ++i ) {
                    TrainP trainP;
                    nn.backpropagate( trainP.coords, trainP.isAbove );
                }

                for ( auto& point : drawSet ) {
                    if ( nn.feedforward( point.coords )[0][0] <= 0.25 )
                        point.color();
                    else if ( nn.feedforward( point.coords )[0][0] <= 0.75 )
                        point.color( 2 );
                    else
                        point.color(1);
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
