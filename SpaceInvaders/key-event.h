#pragma once
#include <SFML/System/Time.hpp>

namespace si {
    namespace controller {
        enum KeyAction {
            GoLeft,          // Sent when the "go left" button is pressed.
            GoRight,         // Sent when the "go right" button is pressed.
            Shoot,           // Sent when the "shoot" button is pressed.

            DebugRestart,    // Sent when the "restart" button is pressed.
        };

        /// Which key was pressed, and for how long?
        struct KeyEvent {
            KeyEvent(KeyAction key, sf::Time dt) : key(key), dt(dt) {}
            KeyAction key;
            sf::Time dt;
        };
    }
}