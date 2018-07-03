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

int train( NeuralNet& nn, int amount );
int getResult( Matrix<float> results );

using namespace std;
int main() {
    NeuralNet nn( 784, {16, 16}, 10 );
    nn.setLearnRate( 0.05 );

    srand( time( NULL ) );
    int count{}, n{}, good{}, total{};
    try {
        Idx idx;
        Matrix <float> results;
        Matrix <float> img = idx.getImage(n);
        Matrix <float> lbl = idx.getLabel(n);
        int digit = int( lbl[0][0] );

        // Pre-training -------------------------------------------------
        int i = 1;
        while (--i) {
            count += train( nn, 1000 );
            std::cout << i << std::endl;
        }
        // get first prediction
        results = nn.feedforward( reshapeMatrix( img ).T() );
        total ++;
        if ( digit == getResult( results ) )
            good ++;
        // --------------------------------------------------------------
        sf::RenderWindow win ( sf::VideoMode( 800, 800 ), "Neural Net");
        fpsClock clock(15);
        while( win.isOpen() ) {
            // Process window events
            switch ( handleEvents( win ) ) {
                case 0: break;
                case 1: return 0;
                case 2:
                    // Hit space for new prediction
                    n = rand()%60000;
                    img = idx.getImage(n);
                    lbl = idx.getLabel(n);
                    digit = int( lbl[0][0] );
                    results = nn.feedforward( reshapeMatrix( img ).T() );
                    total ++;
                    if ( digit == getResult( results ) )
                        good ++;
                    break;
                case 3:
                    // Hit Enter for extra training
                    count += train( nn, 1000 );
                default:
                    break;
            }

            if ( clock.tick() ) {
                auto ratio = float(good)/total*100.f;
                win.clear( sf::Color( 51, 51, 51 ) );
                drawImage( win, img );
                drawText( win, 10 , 300, "Current digit: " + to_string( digit ) );
                drawText( win, 10, 350, "Count: " + to_string( count ) );
                drawText( win, 10, 400, "Error: " + to_string( nn.getError() ) );
                drawText( win, 10, 450, "Good: " + to_string( good ) );
                drawText( win, 10, 500, "Total: " + to_string( total ) );
                drawText( win, 10, 550, "Ratio: " + to_string( ratio ) + "%" );
                drawOutput( win, 500, 10, 20, results.T() );
                win.display();
            }
        }
    } catch (const char* error) {
        std::cout << error << std::endl;
    } catch (std::string err) {
        std::cout << err << std::endl;
    }
    return 0;
}

int getResult( Matrix<float> results ) {
    float highest{};
    int index;
    for ( int i = 0; i < results.getSize().first ; ++i ) {
        if ( results[i][0] > highest ) {
            highest = results[i][0];
            index = i;
        }
    }
    return index;
}

int train( NeuralNet& nn, int amount ) {
    Idx idx;
    int digit;
    Matrix <float> img;
    Matrix <float> lbl;
    Matrix <float> exp_output(1, 10);
    // Pre training loop
    long i = amount;
    while ( --i ) {
        int n = rand()%60000;
        img = idx.getImage(n);
        lbl = idx.getLabel(n);
        digit = int( lbl[0][0] );
        exp_output.fill( 0 );
        exp_output[0][digit] = 1;
        nn.backpropagate( reshapeMatrix( img ).T(), exp_output.T() );
    }
    return amount;
}

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
        // std::vector< TrainP > drawSet;
        // for ( int i = 0; i < 2000; ++i )
        //     drawSet.emplace_back();

        // // Draw the expected -------------------------------------
        // win.clear( sf::Color(51, 51, 51) );
        // for ( auto& point : drawSet )
        //     point.draw(win);
        // win.display();
        // // -------------------------------------------------------
        // // Pretraining -------------------------------------------
        // for ( int j = 0; j < 50; ++j ) {
        //     for ( int i = 0; i < 10000; ++i ) {
        //         TrainP trainP;
        //         nn.backpropagate( trainP.coords, trainP.isAbove );
        //     }
        //     std::cout << j << std::endl;
        // }
        // // -------------------------------------------------------
        // while ( win.isOpen() ) {
        //     if ( clock.tick() ) {
        //         sf::Event event;
        //         while ( win.pollEvent( event ) ) {
        //             if( event.type == sf::Event::Closed )
        //                 win.close();
        //         }

        //         // Training step -------------------------------------
        //         for ( int i = 0; i < 10; ++i ) {
        //             TrainP trainP;
        //             nn.backpropagate( trainP.coords, trainP.isAbove );
        //         }
        //         // ---------------------------------------------------
        //         for ( auto& point : drawSet ) {
        //             auto res = nn.feedforward( point.coords );
        //             if ( res[0][0] && res[1][0] )
        //                 point.color();
        //             else if ( res[0][0] && !res[1][0] )
        //                 point.color( 2 );
        //             else
        //                 point.color(1);
        //         }

        //         win.clear( sf::Color(51, 51, 51) );
        //         for ( auto& point : drawSet )
        //             point.draw(win);
        //         win.display();
        //     }
        // }
        // return 0;
//------------------------------------------------------------------------------