#include "world.h"

namespace si {
    namespace model {
        World::World() {
            invaders = std::vector<Invader>({
                Invader(sf::Vector2f(50, 50)),
                Invader(sf::Vector2f(50, 150)),
            });
        }

        void World::update(const sf::Time &dt) {
            for (auto &e : invaders) {
                e.update(dt);
            }
        }
    }
}