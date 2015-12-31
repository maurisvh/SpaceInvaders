#include "controller.h"

namespace si {
    namespace controller {
        void Controller::registerGame(model::Game *game) {
            addObserver(game);
        }

        void Controller::poll(const sf::Time& dt) {
            using kb = sf::Keyboard;

            // Horizontal movement keys should cancel each other out.
            int xkeys = (kb::isKeyPressed(rightKey) ? 1 : 0)
                      - (kb::isKeyPressed(leftKey)  ? 1 : 0);

            if (xkeys == -1)
                publish(GoLeft);
            else if (xkeys == 1)
                publish(GoRight);

            // Shooting bullets.
            if (kb::isKeyPressed(shootKey))
                publish(Shoot);
        }

        void Controller::press(sf::Keyboard::Key code) {
			if (code == leftKey) {
				publish(MenuLeft);
			} else if (code == rightKey) {
				publish(MenuRight);
			} else if (code == shootKey) {
				publish(MenuSelect);
			} else if (code == debugRestartKey) {
                publish(DebugRestart);
            }
        }
    }
}
