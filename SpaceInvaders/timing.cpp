#include <SFML/System/Clock.hpp>
#include "timing.h"

namespace si {
    Stopwatch::Stopwatch() : clock() {}

    Stopwatch Stopwatch::instance;

    sf::Time Stopwatch::getDelta() {
        return clock.restart();
    }
}
