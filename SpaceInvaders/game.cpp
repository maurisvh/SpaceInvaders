#include "game.h"

namespace si {
    namespace model {
        Game::Game() {
            worlds = std::vector<World>({
                World()
            });
        }

        void Game::update(const sf::Time &dt) {
            for (auto &e : worlds)
                e.update(dt);
        }
    }
}