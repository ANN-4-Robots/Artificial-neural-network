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
// #include "fpsClock.hpp"

using namespace std;
int main() {
    try {

    srand( time( NULL ) ); /*
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
        std::cout << message << std::endl; */
    sf::RenderWindow win ( sf::VideoMode( 800, 800 ), "Neural Net");
    Idx idx;
    int count{};
    
    NeuralNet nn( 784, {12, 12}, 10 );

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
        int digit = int( lbl[0][0] );
        Matrix <float> exp_output(1, 10);

        exp_output.fill( 0 );
        exp_output[0][digit] = 1;
        if(count <= 1000) {
            ++count;
            nn.train( reshapeMatrix( img ).T(), exp_output.T() );
        }

        win.clear( sf::Color( 69, 69, 69 ) );
        drawImage( &win, img );
        drawText( &win, 10 , 300, "Current digit: " + to_string( digit ) );
        drawText( &win, 10, 350, "Count: " + to_string( count ) );
        drawOutput( &win, 500, 10, 20, nn.feedforward( reshapeMatrix( img ).T() ).T() );
       
        win.display();
    }


    return 0;
}
