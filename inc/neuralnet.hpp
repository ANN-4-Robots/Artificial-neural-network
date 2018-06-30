#ifndef NEURALNET_HPP_
#define NEURALNET_HPP_

using namespace std;

class Perceptron {

};

template< typename type >
class Neuralnet {

    vector < type > input;
    vector < type > output;
    vector < Perceptron> hiddenLayer;


    Neuralnet ( unsigned int inputCount = 2, 
                unsigned int hiddenLayerCount = 3,
                unsigned int outputCount = 2 ) {

                    input.resize ( inputCount );
                    input.resize ( outputCount );
                    hiddenLayer.resize ( hiddenLayerCount );
                }
};

#endif