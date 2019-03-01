#include "fpsClock.hpp"

fpsClock::fpsClock(int skipTime_) {
    presentTime = clock.getElapsedTime();
    skipTime = sf::milliseconds(int(1000/skipTime_));
    prevTime = sf::milliseconds(presentTime.asMilliseconds());
}

bool fpsClock::tick() {
    presentTime = clock.getElapsedTime();
    if(presentTime.asMilliseconds() >= prevTime.asMilliseconds() + skipTime.asMilliseconds()) {
        prevTime = presentTime;
        return true;
    } else
        return false;
}

double fpsClock::interpolation() {
    presentTime = clock.getElapsedTime();
    double interpolation = double((presentTime - prevTime) / skipTime);
    return interpolation;
}