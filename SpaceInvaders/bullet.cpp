#include "bullet.h"
#include "constants.h"

namespace si {
    namespace model {
        const float Bullet::size = 8.0f;
        Bullet::Bullet(const sf::Vector2f& p, float speed, float angle)
            : IPhysical(p, size), speed(speed), angle(angle) {}

        void Bullet::movement(const sf::Time& dt) {
            sf::Vector2f dir = sf::Vector2f(cosf(angle), sinf(angle));
            moveBy(dir * speed * dt.asSeconds());
            if (offScreen()) destroy();
        }

        void Bullet::hit(IShootable& e) {
            e.shot();
            destroy();
        }

        bool Bullet::harmsPlayer() const { return false; }
        bool Bullet::harmsInvader() const { return false; }
        bool Bullet::harmsShield() const { return true; }

        void Bullet::update(const sf::Time& dt) {
            movement(dt);
            publish(*this);
        }

        float PlayerBullet::randomAngle() {
            return angle::up + RandomGenerator::rg.random() * 0.1f - 0.05f;
        }

        PlayerBullet::PlayerBullet(const sf::Vector2f& p)
            : Bullet(p, 200.0f, randomAngle()), IPhysical(p, size) {}

        bool PlayerBullet::harmsInvader() const { return true; }
    }
}