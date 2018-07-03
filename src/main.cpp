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
    try {

    srand( time( NULL ) );
    fpsClock clock(1);
    sf::RenderWindow win ( sf::VideoMode( width, height ), "Neural Net");

    NeuralNet nn( 2, {10,5,10}, 2 );

// XOR -------------------------------------------------------------------------
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

    // nn.setLearnRate(0.01);
    // long long i = 1000000;
    // while (--i) {
    //     int random = rand()%4;
    //     nn.backpropagate( trainSet[random], ideal[random] );
    // }
    // for ( int i = 0; i < 4; ++i)
    //     std::cout << nn.feedforward( trainSet[i] );
//------------------------------------------------------------------------------

// GRAPHICAL TEST --------------------------------------------------------------
// SET UP GRAPHICAL AREA IN POINT LINE 50
        std::vector< TrainP > drawSet;
        for ( int i = 0; i < 2000; ++i )
            drawSet.emplace_back();

        // Draw the expected -------------------------------------
        win.clear( sf::Color(51, 51, 51) );
        for ( auto& point : drawSet )
            point.draw(win);
        win.display();
        // -------------------------------------------------------
        // Pretraining -------------------------------------------
        for ( int j = 0; j < 50; ++j ) {
            for ( int i = 0; i < 10000; ++i ) {
                TrainP trainP;
                nn.backpropagate( trainP.coords, trainP.isAbove );
            }
            std::cout << j << std::endl;
        }
        // -------------------------------------------------------
        while ( win.isOpen() ) {
            if ( clock.tick() ) {
                sf::Event event;
                while ( win.pollEvent( event ) ) {
                    if( event.type == sf::Event::Closed )
                        win.close();
                }

                // Training step -------------------------------------
                for ( int i = 0; i < 10; ++i ) {
                    TrainP trainP;
                    nn.backpropagate( trainP.coords, trainP.isAbove );
                }
                // ---------------------------------------------------
                for ( auto& point : drawSet ) {
                    auto res = nn.feedforward( point.coords );
                    if ( res[0][0] && res[1][0] )
                        point.color();
                    else if ( res[0][0] && !res[1][0] )
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
//------------------------------------------------------------------------------
    } catch ( const char* message ) {
        std::cout << message << std::endl;
    }
}
