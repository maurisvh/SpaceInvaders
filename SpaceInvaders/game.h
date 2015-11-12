#pragma once
#include "entity.h"
#include "world.h"

namespace si {
    namespace model {
        class Game : public Entity {
        public:
            Game();

            void update(const sf::Time &dt) override;

        private:
            std::vector<World> worlds;
        };
    }
}