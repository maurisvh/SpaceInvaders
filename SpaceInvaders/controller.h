#pragma once
#include <SFML/Window/Keyboard.hpp>
#include "observer.h"
#include "game.h"
#include "key-event.h"

namespace si {
    namespace controller {
        class Controller : public virtual Observable<KeyAction> {
        public:
            /// The keyboard controls for the game.
            using Key = sf::Keyboard::Key;
            const Key leftKey = Key::Left;
            const Key rightKey = Key::Right;
            const Key shootKey = Key::X;

            /// Some additional debug keys.
            const Key debugRestartKey = Key::R;

            /// Register a Game object to observe this controller.
            void registerGame(model::Game *game);

            /// Poll for keypresses. `dt` is the interval since the last tick,
            /// so it represents the length of the KeyEvents to send.
            void poll(const sf::Time &dt);

            /// Called whenever a new key is pressed down.
            void press(sf::Keyboard::Key code);
        };
    }
}