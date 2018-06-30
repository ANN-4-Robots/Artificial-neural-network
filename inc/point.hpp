#ifndef POINT_HPP_
#define POINT_HPP_

const int width = 800, height = 800;

const float A = 0.25;
const float B = 200;
const float Bias = 1;

float f( int x ) {
    return A*x + B;
}

struct Point {
    std::vector<int> coords;

    Point() {
        coords = { rand()%width - width/2, rand()%height - width/2 };
    }
    Point( int _x, int _y ) {
        coords = { _x, _y };
    }
};

struct TrainP :public Point {
    bool isAbove;
    sf::CircleShape body;

    TrainP() : Point() {
        ( coords[1] < f( coords[0] ) ) ?
            isAbove = false :
            isAbove = true;
        coords.push_back( Bias );

        if ( !isAbove )
            body.setFillColor( sf::Color(0,255,0) );
        // else
        // body.setFillColor( sf::Color(255,0,0) );
        // std::cout << "X: " << coords[0] << "\t Y: " << coords[1] << "\t ABOVE: " << isAbove << "\n";

        body.setRadius( 2 );
        body.setPosition( coords[0]+width/2, height/2-coords[1] );
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