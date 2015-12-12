#pragma once
#include "entity.h"
#include "bullet.h"

namespace si {
    namespace model {
        class Invader : public PathedEntity,
            public virtual Observable<Message>,
            public virtual ISpawns<EnemyBullet>,
            public virtual IPlayerBulletTarget {
        public:
            static const float size;

            explicit Invader(const sf::Vector2f &p);

            int health() const;

            float pathDrag() const override;
            sf::Vector2f path(sf::Time time) const override;

            void shot() override;

            void update(const sf::Time &dt) override;

        private:
            float xWigglePeriod, yWigglePeriod, wigglePhase;
            int m_health;
        };
    }
}