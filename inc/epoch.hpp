#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>
#include <thread>
#include <cmath>
#include <fstream>
#include "matrix.hpp"
#include "point.hpp"
#include "neuralnet.hpp"
#include "idx.hpp"
#include "display.hpp"

class Epoch {
    public:
    Epoch() {
        std::thread t1( log( {16, 16, 16}, 0.02 ) );
        std::thread t2( log( {16, 16, 16}, 0.01 ) );
        std::thread t3( log( {16, 16, 16}, 0.03 ) );
        std::thread t4( log( {16, 16, 16}, 0.04 ) );
        t1.join();
        t2.join();
        t3.join();
        t4.join();
    }
    void log( std::initializer_list<int> hidden, float lr ) {
        long long n{};
        std::ofstream fout;
        //tworzenie nazwy pliku
        std::string name{};
        for ( auto i = hidden.begin(); i < hidden.end(); ++i )
            name += std::to_string( *i )+"_";
        name += std::to_string( int(1000*lr) );
        //otwarcie
        fout.open( (name + ".csv").c_str() );

        NeuralNet nn( 784, hidden, 10 );
        //trening do 5mln
        while ( n++ < 100 ) {
            train( nn, 50000 );
            auto res = test( nn, 10000 );
            fout << n*50000 << ";\t" << res.first << ";\t" << res.second << ";\n";
        }
        fout.close();
        //zapisanie sieci
        fout.open( (name +"_net.txt").c_str() );
        auto wages = nn.getWages();
        auto biases = nn.getBiases();
        fout << "Wages:\n\n";
        for ( auto& wage : wages )
            fout << wage << std::endl;
        fout << "\nBiases:\n\n";
        for ( auto& bias : biases )
            fout << bias << std::endl;
    }

    int getResult( Matrix<float> results ) {
        float highest{};
        int index;
        for ( int i = 0; i < results.getSize().first ; ++i ) {
            if ( results[i][0] > highest ) {
                highest = results[i][0];
                index = i;
            }
        }
        return index;
    }

    void train( NeuralNet& nn, long amount ) {
        Idx idx;
        int digit;
        Matrix <float> img;
        Matrix <float> lbl;
        Matrix <float> exp_output(1, 10);
        long i = amount;
        while ( --i ) {
            int b = 1000;
            while ( b-- ) {
                int n = rand()%60000;
                img = idx.getImage(n);
                lbl = idx.getLabel(n);
                digit = int( lbl[0][0] );
                exp_output.fill( 0 );
                exp_output[0][digit] = 1;
                nn.backpropagate( reshapeMatrix( img ).T(), exp_output.T() );
            }
        }
    }

    std::pair<double, double> test( NeuralNet& nn, int amount ) {
        double error{};
        int i{};
        while ( i < amount ) {
            Matrix<float> img = idx.getImage(i);
            Matrix<float> lbl = idx.getLabel(i);
            int digit = int( lbl[0][0] );
            results = nn.feedforward( reshapeMatrix( img ).T() );
            total ++;
            if ( digit == getResult( results ) )
                good ++;
            error += nn.getError();
        }
        return std::pair(error/amount, double(good)/total*100);
    }
}