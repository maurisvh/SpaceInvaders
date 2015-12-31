#pragma once
#include <SFML/System/Time.hpp>

namespace si {
    namespace controller {
        enum KeyAction {
            GoLeft,          // Sent each update if the "go left" button is held.
            GoRight,         // Sent each update if the "go right" button is held.
            Shoot,           // Sent each update if the "shoot" button is held.
            
			MenuLeft,		 // Sent once when the "go left" button is pressed.
			MenuRight,       // Sent once when the "go right" button is pressed.
			MenuSelect,      // Sent once when the "shoot" button is pressed.
			Confirm,         // Sent once when the "confirm" button is pressed.
            DebugRestart,    // Sent once when the "restart" button is pressed.
        };
    }
}