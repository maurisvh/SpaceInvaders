#pragma once
#include "entity.h"
#include "random.h"

namespace si {
    namespace model {
        class Bullet : public Entity, public virtual IPhysical,
            public virtual Observable<Entity> {
        public:
            Bullet(const sf::Vector2f &p, float speed, float angle);
            void update(const sf::Time& dt) override;
            const static float size;

            /// Called when a susceptible entity is hit by a bullet.
            void hit(IShootable& e);
        
        protected:
            float speed, angle;

            /// Move forward (called each update).
            void movement(const sf::Time& dt);

            /// Does this bullet harm the player? False by default.
            virtual bool harmsPlayer() const;
            
            /// Does this bullet harm the invaders? False by default.
            virtual bool harmsInvader() const;
            
            /// Does this bullet harm the shields? True by default.
            virtual bool harmsShield() const;
        };

        class PlayerBullet : public Bullet {
        public:
            explicit PlayerBullet(const sf::Vector2f &p);
        protected:
            static float randomAngle();
            virtual bool harmsInvader() const override;
        };
    }
}