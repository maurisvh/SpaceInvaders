#pragma once
#include "entity.h"
#include "random.h"
#include "message.h"

namespace si {
    namespace model {
        class Bullet : public Entity, public virtual IPhysical,
            public virtual Observable<Message> {
        public:
            Bullet(const sf::Vector2f &p, float speed, float angle);
            void update(const sf::Time& dt) override;
            const static float size;
        
        protected:
            float speed, angle;

            /// Move forward (called each update).
            void movement(const sf::Time& dt);
        };

        /// A bullet fired by the player.
        class PlayerBullet : public Bullet {
        public:
            explicit PlayerBullet(const sf::Vector2f &p);
            void hitEnemy(IPlayerBulletTarget &e);

        protected:
            static float randomAngle();
        };

        /// A bullet fired by an invader.
        class EnemyBullet : public Bullet {
        public:
            explicit EnemyBullet(const sf::Vector2f &p, float angle);
            void hitPlayer(IEnemyBulletTarget &e);
        };


    }
}