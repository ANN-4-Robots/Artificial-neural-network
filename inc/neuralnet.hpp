#ifndef NEURALNET_HPP_
#define NEURALNET_HPP_

using namespace std;

class Perceptron {

};

template< typename type >
class Neuralnet {

    vector <type> input;
    vector <type> output;
    vector <Perceptron> hiddenLayer;

    int *ih_weight;

    Neuralnet ( unsigned int inputCount = 2, 
                unsigned int hiddenLayerCount = 3,
                unsigned int outputCount = 2 ) {

                    input.resize ( inputCount + 1 );        //Vector holding all input values and bias = 1
                    input.resize ( outputCount );
                    hiddenLayer.resize ( hiddenLayerCount );

                    ih_weight = new Matrix <type> ( 1, inputCount + 1 );
                }
};

#endif