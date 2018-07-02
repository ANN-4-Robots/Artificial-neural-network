#ifndef POINT_HPP_
#define POINT_HPP_

const int width = 800, height = 800;

const float A = 1;
const float B = 200;

const float C = 1;
const float D = -200;

const float E = -2;
const float F = 50;

const float G = -2;
const float H = -50;

const float Bias = 1;

float f1( float x ) {
    return A* x + B;
}
float f2( float x ) {
    return C* x + D;
}
float f3( float x ) {
    return E* x + F;
}
float f4( float x ) {
    return G* x + H;
}


struct Point {
    Matrix<float> coords;

    Point() {
        coords = Matrix<float>{ {float(rand()%width - width/2)}, {float(rand()%height - width/2)} };
    }
    Point( float _x, float _y ) {
        coords = { {_x}, {_y} };
    }
};

struct TrainP :public Point {
    bool isAbove;
    sf::CircleShape body;

    TrainP() : Point() {
        ( coords[1][0] < f1( coords[0][0] ) &&
          coords[1][0] > f2( coords[0][0] ) ) ?
            isAbove = false :
            isAbove = true;

        if ( !isAbove )
            body.setFillColor( sf::Color(0,255,0) );
        // else
        // body.setFillColor( sf::Color(255,0,0) );
        // std::cout << "X: " << coords[0] << "\t Y: " << coords[1] << "\t ABOVE: " << isAbove << "\n";

        body.setRadius( 2 );
        body.setPosition( coords[0][0]+width/2, height/2-coords[1][0] );
        // body.setFillColor( sf::Color(255,0,0) );
    }

    void color( bool col = true ) {
        if ( col )
            body.setFillColor( sf::Color(0,255,0) );
        else
            body.setFillColor( sf::Color(255,0,0) );
    }

    void draw( sf::RenderWindow& win ) {
        win.draw( body );
    }
};

#endif