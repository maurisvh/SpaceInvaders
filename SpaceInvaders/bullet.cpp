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

        void Bullet::update(const sf::Time& dt) {
            movement(dt);
            publish(EntityMessage(position(), typeid(Bullet)));
        }

        float PlayerBullet::randomAngle() {
            return angle::up + RandomGenerator::rg.random(-0.05f, 0.05f);
        }

        PlayerBullet::PlayerBullet(const sf::Vector2f& p)
            : Bullet(p, 200.0f, randomAngle()), IPhysical(p, size) {}

        void PlayerBullet::hitEnemy(IPlayerBulletTarget& e) {
            e.shot();
            destroy();
        }

        EnemyBullet::EnemyBullet(const sf::Vector2f& p, float angle)
            : Bullet(p, 200.0f, angle), IPhysical(p, size) {}

        void EnemyBullet::hitPlayer(IEnemyBulletTarget& e) {
            e.shot();
            destroy();
        }
    }
}