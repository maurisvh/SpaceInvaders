#pragma once
#include "entity.h"

namespace si {
    namespace model {
        class Invader : public Entity, public IPhysical {
        public:
            static const double size;

            explicit Invader(const sf::Vector2f &p);

            void update(const sf::Time &dt) override;
        };
    }
}