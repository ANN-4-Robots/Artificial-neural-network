#ifndef NEURALNET_HPP_
#define NEURALNET_HPP_

// #include "matrix.hpp"

class NeuralNet {
    int hLayers;
    int iNum;
    int oNum;
    float learnRate = 0.1;
    float error;

    std::vector< Matrix<float> > hValues;
    std::vector< Matrix<float> > hWages;
    std::vector< Matrix<float> > biases;

    public:
    NeuralNet() :learnRate{0.5}, error{0} {}

    NeuralNet( int inputsNum, int hiddenNum, int outputsNum ) :learnRate{0.5}, error{0} {
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

    NeuralNet ( int inputsNum, std::initializer_list<int> hNums, int outputsNum ) :learnRate{0.5}, error{0} {
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
        // error
        auto lSquares = []( float& x ){ x = pow(x,2)/2; };

        // Get valued calculated by current state of NN
        Matrix<float> results = feedforward ( inputs );

        // Vectors of matrices holding error values of each layer 
        std::vector< Matrix<float> > errors;
        errors.resize( hWages.size() );
        // Calculate the error of NN's output
        Matrix<float> finalErr = results - expected;
        // get the derivative of the sum value of outputs
        auto dValue = results;
        dValue.map( dSigmoid ); 
        // push the error maped by dValues to errors
        errors.back() = Matrix<float>::elementwise( finalErr, dValue );
        // Calculate total error
        finalErr = expected - results;
        // apply x^2/2 
        error = 0;
        finalErr.map( lSquares );
        for ( int i = 0; i < finalErr.getSize().first; ++i )
            error += finalErr[i][0];

        // Calculate the errors of hidden layers
        for ( int i = hLayers-1; i >= 0; --i ) {
            dValue = hValues[i];
            dValue.map( dSigmoid ); 
            errors[i] = hWages[i+1].T() * errors[i+1];
            errors[i] = Matrix<float>::elementwise( errors[i], dValue );
        }

        // Calculating gradient for all weights and biases
        std::vector<Matrix<float>> gradsW;
        std::vector<Matrix<float>> gradsB;
        gradsW.resize( hLayers+1 );
        gradsB.resize( hLayers+1 );
        
        for ( int i = hLayers-1; i >= 0; --i ) {
            gradsW[i+1] = errors[i+1] * hValues[i].T();
            gradsB[i+1] = errors[i+1];
        }
        gradsW.front() = errors.front() * inputs.T();
        gradsB.front() = errors.front();

        // Apply gradients to all wages and biases
        hWages.front() = hWages.front() - gradsW.front() * learnRate;
        biases.front() = biases.front() - gradsB.front() * learnRate;
        for ( int i = 1; i < hLayers+1; ++i ) {
            hWages[i] = hWages[i] - gradsW[i] * learnRate;
            biases[i] = biases[i] - gradsB[i] * learnRate;
        }
    }

    void saveToFile( std::string fileName ) {
        std::ofstream fout;
        fout.open( fileName.c_str() );
        // First number must be number of hidden layers, second learnRate
        fout << hLayers << " " << learnRate << std::endl;
        fout << iNum << " ";
        for ( auto& h : hValues )
            fout << h.getSize().first << " ";
        fout << oNum << std::endl;
        for ( auto& wage : hWages )
            fout << wage << std::endl;
        for ( auto& bias : biases )
            fout << bias << std::endl;
        fout.close();
    }

    void loadFromFile( std::string fileName ) {
        hValues.clear();
        hWages.clear();
        biases.clear();
        std::ifstream fin;
        fin.open( fileName.c_str() );
        fin >> hLayers >> learnRate >> iNum;
        // emplace hidden layers
        for ( int i = 0, hVal; i < hLayers; ++i ) {
            fin >> hVal;
            hValues.emplace_back( hVal, 1 );
        }
        fin >> oNum;
        int n = hValues.front().getSize().first;
        hWages.emplace_back( n, iNum );
        // Load Wages for first layer
        for ( int i = 0; i < n; ++i )
            for ( int j = 0; j < iNum; ++j )
                fin >> hWages.front()[i][j];
        // Load wages for hidden
        for ( int k = 1; k < hLayers; ++k ) {
            n = hValues[k].getSize().first;
            int m = hValues[k-1].getSize().first;
            hWages.emplace_back( n, m );
            for ( int i = 0; i < n; ++i )
                for ( int j = 0; j < m; ++j )
                    fin >> hWages[k][i][j];
        }
        // Load wages for last layer
        n = hValues.back().getSize().first;
        hWages.emplace_back( oNum, n );
        for ( int i = 0; i < oNum; ++i )
            for ( int j = 0; j < n; ++j )
                fin >> hWages.back()[i][j];
        // Load biases for hidden
        for ( int k = 0; k < hLayers; ++k ) {
            n = hValues[k].getSize().first;
            biases.emplace_back( n, 1 );
            for ( int i = 0; i < n; ++i )
                fin >> biases[k][i][0];
        }
        //and the last bias
        biases.emplace_back( oNum, 1 );
        for ( int i = 0; i < oNum; ++i )
            fin >> biases.back()[i][0];
        fin.close();
    }

    std::vector<Matrix<float>> getWages() {
        return hWages;
    }

    std::vector<Matrix<float>> getBiases() {
        return biases;
    }

    float getError() {
        return error;
    }

    void setLearnRate( float lr ) {
        learnRate = lr;
    }
};

#endif