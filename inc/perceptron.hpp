#ifndef PERCEPTRON_HPP_
#define PERCEPTRON_HPP_

struct Perceptron {
    std::vector< float > wages;
    float value;
    const float ratio = 0.001;

    public:
    Perceptron( int inputsNum = 2 ) {
        wages.resize( inputsNum + 1 );
        for ( auto& wage : wages ) {
            wage = float(rand()%1000) / 500 -1;
        }
    }
    
    // Method for returning a normalized value
    float sigmoid() {
        return 1/(1 + pow( M_E, -value));
    }

    // Train perceptron
    float train( std::vector<int> inputs, int expected ) {
        auto output = think( inputs ) < 0.5 ? 0 : 1;
        auto error = expected - output;

        for ( int i = 0; i < inputs.size(); ++i ){
            wages[i] += inputs[i] * error * ratio;
        }

        return error;
    }
    // Compute the output based on given inputs and current
    // values of the weights
    float think( std::vector< int > inputs ) {
        float sum{};
        for (int i = 0; i < inputs.size(); i++) {
            sum += wages[i] * inputs[i];
        }
        value = sum;
        return sigmoid();
    }
};

#endif
