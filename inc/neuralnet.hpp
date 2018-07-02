#ifndef NEURALNET_HPP_
#define NEURALNET_HPP_

// #include "matrix.hpp"

class NeuralNet {
    int hLayers;
    int iNum;
    int oNum;
    float learnRate;

    std::vector< Matrix<float> > hValues;
    std::vector< Matrix<float> > hWages;
    std::vector< Matrix<float> > biases;

    public:
    NeuralNet( int inputsNum, int hiddenNum, int outputsNum ) :learnRate{0.5} {
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

    NeuralNet ( int inputsNum, std::initializer_list<int> hNums, int outputsNum ) :learnRate{0.5} {
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
        auto sigmoid = []( float& x ){ x = 1/(1+pow(M_E,-x)); };

        // get the value for the first hidden layer
        hValues[0] = (hWages[0] * inputs) + biases[0];
        hValues[0].map( sigmoid );

        // get the value for the rest of hidden
        for ( int i = 1; i < hLayers; ++i ) {
            hValues[i] = (hWages[i] * hValues[i-1]) + biases[i];
            hValues[i].map( sigmoid );
        }

        // get the output value
        auto output = (*hWages.rbegin() * *hValues.rbegin()) + *biases.rbegin();
        output.map( sigmoid );
        return output;
    }

    void backpropagate( Matrix <float> inputs, Matrix <float> expected ) {
        // Sigmoid derivative function
        auto dSigmoid = []( float& x ){ x = x*(1-x); };
        //auto lSquares = []( float& x ){ x = pow(x,2)/2; };

        // Get valued calculated by current state of NN
        Matrix<float> results = feedforward ( inputs );

        // Vectors of matrices holding error values of each layer 
        std::vector< Matrix<float> > errors;
        errors.resize( hWages.size() );
        // Calculate the error of NN's output
        Matrix<float> finalErr = expected - results;
        // apply x^2/2 
        //finalErr.map( lSquares );
        errors.back() = finalErr;

        // Calculate the errors of hidden layers
        for ( int i = errors.size() - 1; i > 0; --i ) {
            errors[i - 1] = hWages[i].T() * errors[i];
        }

        // Back propagate wages towards it's gradient
        // Last wages
        results.map( dSigmoid );
        Matrix <float> deltaWage = Matrix <float>::elementwise( results, finalErr ) * hValues.back().T() * learnRate;
        Matrix <float> deltaBias = Matrix <float>::elementwise( results, finalErr ) * learnRate;
        hWages.back() = hWages.back() + deltaWage;
        biases.back() = biases.back() + deltaBias;
        // All hidden
        for ( int i = hLayers -1; i > 0; --i ) {
            hValues[i].map( dSigmoid );
            deltaWage = Matrix <float>::elementwise( hValues[i], errors[i] ) * hValues[i-1].T() * learnRate;
            deltaBias = Matrix <float>::elementwise( hValues[i], errors[i] ) * learnRate;
            hWages[i] = hWages[i] + deltaWage;
            biases[i] = biases[i] + deltaBias;
        }
        // First wages
        hValues.front().map( dSigmoid );
        deltaWage = Matrix <float>::elementwise( hValues.front(), errors.front() ) * inputs.T() * learnRate;
        deltaBias = Matrix <float>::elementwise( hValues.front(), errors.front() ) * learnRate;
        hWages.front() = hWages.front() + deltaWage;
        biases.front() = biases.front() + deltaBias;
    }

    void setLearnRate( float lr ) {
        learnRate = lr;
    }
};

#endif