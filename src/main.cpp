#include <iostream>
#include <vector>
#include <cstdlib>
#include <cmath>
#include <SFML/Graphics.hpp>
//#include "point.hpp"
#include "matrix.hpp"
#include "neuralnet.hpp"


int main() {
    srand( time( NULL ) );

    NeuralNet nn( 3, {5,4,3}, 2 );

    Matrix<float> inputs( {{1,2,3}} );
    Matrix<float> expected( {{0.2,0.9}} );
    try {
        // std::cout << nn.feedforward( inputs.T() );
        nn.train( inputs.T() , expected.T() );
    } catch ( char const* error ) {
        // std::cout << error << std::endl;
    }
    
    return 0;
}
