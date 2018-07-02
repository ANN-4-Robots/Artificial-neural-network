#ifndef FPSCLOCK_HPP
#define FPSCLOCK_HPP

// Maciej Zwoliński 
// 21 / 05/ 2018

// Simple fps handling class for sfml
// It bases on sf::Clock class
// As init value for fpsClock you pass an amount of fps you want to aquire
// the tick() method control frame rate and interpolaiton returns interpolated value between frames

#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>

class fpsClock {
    sf::Clock clock;
    sf::Time presentTime;
    sf::Time skipTime;
    sf::Time prevTime;

    public:
    fpsClock( int skipTime_ );
    bool tick();
    double interpolation();
};

#endif
