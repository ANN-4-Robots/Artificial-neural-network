#include <SFML/Graphics.hpp>
//#include "point.hpp"
#include "neuralnet.hpp"


int main() {
    srand( time( NULL ) );

    NeuralNet nn( 3, 5, 1 );

    Matrix<float> inputs( {{1,3,5}} );
    try {
        std::cout << nn.feedforward( inputs.T() );
    } catch ( char const* error ) {
        std::cout << error << std::endl;
    }
    
    return 0;
}
