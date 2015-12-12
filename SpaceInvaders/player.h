#pragma once
#include "entity.h"
#include "bullet.h"

namespace si {
    namespace model {
        class Player : public Entity, public virtual IPhysical,
            public virtual Observable<Message>,
            public virtual ISpawns<PlayerBullet>,
            public virtual IEnemyBulletTarget {
        public:
            static const float size;

            explicit Player(const sf::Vector2f& p);
            void update(const sf::Time& dt) override;

            void shot() override;

            void setHorizontalAcceleration(const float a);
            void shoot();

        private:
            /// Horizontal acceleration and speed.
            float haccel, hspeed;
            /// Timeout on firing the next bullet.
            sf::Time bulletTimeout;

            void clampHorizontalPosition(float margin);
            void applyAcceleration(const sf::Time& dt);
            void applySpeed(const sf::Time& dt);
            void applyBulletTimeout(const sf::Time dt);
        };
    }
}