#ifndef NEURALNET_HPP_
#define NEURALNET_HPP_

using namespace std;

class Perceptron {
    float bias;
};

template< typename type >
class Neuralnet {
    public:
    vector <type> input;
    vector <type> output;


    Matrix <type> *weights;

    Neuralnet ( unsigned int inputCount = 2, 
                unsigned int outputCount = 2 ) {

                    input.resize ( inputCount + 1 );        //Vector holding all input values and bias = 1
                    input.resize ( outputCount );

                    weights = new Matrix <type> ( inputCount + 1, outputCount );
                    weights->randomize ( 1, -1 );

                    // for ( int i = 0; i < outputCount; ++i ) {
                    //     weights[]
                    // }

                    cout << *weights;
                }
};

#endif