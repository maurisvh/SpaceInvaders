#pragma once
#include <SFML/System/Clock.hpp>

namespace si {
    class Stopwatch {
    public:
        /// The singleton Stopwatch instance.
        static Stopwatch instance;

        /// Get the elapsed time since the previous call to `getDelta`,
        /// or on the first call, the time since the clock was started.
        sf::Time getDelta();

    private:
        Stopwatch();

        sf::Clock clock;

        // This is a singleton class. Don't allow copies.
        Stopwatch(Stopwatch const &) = delete;
        void operator=(Stopwatch const &) = delete;
    };
}
