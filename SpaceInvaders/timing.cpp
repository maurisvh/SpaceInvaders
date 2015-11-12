#include <SFML/System/Clock.hpp>
#include "timing.h"

namespace si {
    Stopwatch::Stopwatch() : clock() {}

    Stopwatch &Stopwatch::instance() {
        static Stopwatch stopwatch;
        return stopwatch;
    }

    sf::Time Stopwatch::getDelta() {
        return clock.restart();
    }
}
