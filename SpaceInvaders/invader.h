#pragma once
#include "entity.h"

namespace si {
    namespace model {
        class Invader : public PathedEntity,
            public virtual Observable<Entity> {
            float xWigglePeriod, yWigglePeriod, wigglePhase;

        public:
            static const float size;

            explicit Invader(const sf::Vector2f &p);

            float pathDrag() const override;
            sf::Vector2f path(sf::Time time) const override;

            void update(const sf::Time &dt) override;
        };
    }
}