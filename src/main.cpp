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

    NeuralNet nn( 3, {5,3,5}, 2 );

    Matrix<float> inputs( {{1,2,3}} );
    try {
        std::cout << nn.feedforward( inputs.T() );
        nn.train( inputs.T() , {{2,4}} );
    } catch ( char const* error ) {
        std::cout << error << std::endl;
    }
    
    return 0;
}
