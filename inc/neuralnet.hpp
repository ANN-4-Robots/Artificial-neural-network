#ifndef NEURALNET_HPP_
#define NEURALNET_HPP_

#include "matrix.hpp"

class Neuralnet {
    int hLayers;

    std::vector< Matrix<float> > hValues;
    std::vector< Matrix<float> > hWages;

    public:
    Neuralnet( int inputsNum, int hiddenNum, int outputsNum ) {
        hValues.emplace_back( hiddenNum, 1 );
        hWages.emplace_back( inputsNum, hiddenNum );
        hWages.emplace_back( hiddenNum, outputsNum );
    }
};

#endif