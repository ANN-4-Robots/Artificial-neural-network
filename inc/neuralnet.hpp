#ifndef NEURALNET_HPP_
#define NEURALNET_HPP_

#include "matrix.hpp"

class NeuralNet {
    int hLayers;
    int iNum;
    int oNum;

    std::vector< Matrix<float> > hValues;
    std::vector< Matrix<float> > hWages;
    std::vector< Matrix<float> > biases;

    public:
    NeuralNet( int inputsNum, int hiddenNum, int outputsNum ) {
        iNum = inputsNum;
        hLayers = 1;
        oNum = outputsNum;

        hValues.emplace_back( hiddenNum, 1 );
        hWages.emplace_back( hiddenNum, inputsNum );
        hWages.emplace_back( outputsNum, hiddenNum );

        biases.emplace_back( hiddenNum, 1 );
        biases.emplace_back( outputsNum, 1 );

        for ( auto& matrix : hWages )
            matrix.randomize( 1, -1 );
    }

    NeuralNet ( int inputsNum, std::initializer_list<int> hNums, int outputsNum ) {
        iNum = inputsNum;
        hLayers = hNums.size();
        oNum = outputsNum;

        // set first hlayer
        auto itr = hNums.begin();
        hWages.emplace_back( *itr, inputsNum );
        hValues.emplace_back( *itr, 1 );
        biases.emplace_back( *itr, 1 );
        itr++;
        // and the rest
        for (; itr != hNums.end(); ++itr ) {
            hValues.emplace_back( *itr, 1 );
            biases.emplace_back( *itr, 1 );
            hWages.emplace_back( *itr, *(itr-1) );
        }
        // and the output wages
        hWages.emplace_back( outputsNum, *(hNums.end()-1) );
        biases.emplace_back( outputsNum, 1 );
        // and randomize all wages
        for ( auto& matrix : hWages )
            matrix.randomize( 1, -1 );
        for ( auto& matrix : biases )
            matrix.randomize( 1, -1 );
    }

    // without biases
    Matrix<float> feedforward( Matrix<float> inputs ) {
        // Sigmoid function
        auto sigmoid = []( float& x ){ return 1/(1+pow(M_E,-x)); };
        // get the value for the first hidden layer
        hValues[0] = hWages[0] * inputs + biases[0];
        hValues[0].map( sigmoid );
        // get the value for the rest of hidden
        for ( int i = 1; i < hLayers; ++i ) {
            hValues[i] = hWages[i] * hValues[i-1] + biases[0];
            hValues[i].map( sigmoid );
        }
        // get the output value
        auto output = *hWages.rbegin() * *hValues.rbegin() + *biases.rbegin();
        output.map( sigmoid );
        return output;
    }
};

#endif