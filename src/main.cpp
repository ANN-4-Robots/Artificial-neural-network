#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <cmath>
#include <fstream>
#include "matrix.hpp"
#include "point.hpp"
#include "neuralnet.hpp"
#include "idx.hpp"
#include "fpsClock.hpp"

using namespace std;
int main() {
    srand( time( NULL ) );
    Idx idx;
    
    for( int i = 0; i < 10; ++i ) {
        cout << idx.getImage(i);
        cout << idx.getLabel(i) << "\n\n\n";
    }

    return 0;
}
