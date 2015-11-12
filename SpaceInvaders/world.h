#pragma once
#include "entity.h"
#include <vector>
#include "invader.h"

namespace si {
    namespace model {
        /// The game world, containing a player, bullets, shields, enemies...
        /// If this is in the `Game` entity, the game is in progress.
        class World : public Entity {
        public:
            World();

            void update(const sf::Time &dt) override;

        private:
            std::vector<Invader> invaders;
        };
    }
}