#include "controller.h"

namespace si {
    namespace controller {
        void Controller::registerGame(const std::shared_ptr<model::Game> game) {
            addObserver(game);
        }

        void Controller::poll(const sf::Time& dt) {
            using kb = sf::Keyboard;

            // Horizontal movement. Keys should cancel each other out.
            int xkeys = (kb::isKeyPressed(rightKey) ? 1 : 0)
                      - (kb::isKeyPressed(leftKey)  ? 1 : 0);

            if (xkeys == -1)
                publish(KeyEvent(GoLeft, dt));
            else if (xkeys == 1)
                publish(KeyEvent(GoRight, dt));

            // Shooting bullets.
            if (kb::isKeyPressed(shootKey))
                publish(KeyEvent(Shoot, dt));
        }
    }
}
