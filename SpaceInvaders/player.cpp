#include "player.h"
#include "constants.h"
#include "bullet.h"

namespace si {
    namespace model {
        const float Player::size = 20.0;
        Player::Player(const sf::Vector2f& p)
            : Entity(), IPhysical(p, size), hspeed(0.0) {}

        void Player::applyAcceleration(const sf::Time& dt) {
            hspeed += haccel * dt.asSeconds();
            haccel = 0.0f;
        }

        void Player::applySpeed(const sf::Time& dt) {
            hspeed = std::min(200.0f, std::max(-200.0f, hspeed));
            hspeed *= powf(0.05f, dt.asSeconds());
            moveBy(sf::Vector2f(hspeed * dt.asSeconds(), 0.0));
        }

        void Player::applyBulletTimeout(const sf::Time dt) {
            bulletTimeout -= dt;
            if (bulletTimeout < sf::Time::Zero)
                bulletTimeout = sf::Time::Zero;
        }

        void Player::clampHorizontalPosition(float margin = 30.0f) {
            if (position().x < margin) {
                hspeed *= -0.5f;
                moveTo(sf::Vector2f(margin, position().y));
            } else if (position().x > screenWidth - margin) {
                hspeed *= -0.5f;
                moveTo(sf::Vector2f(screenWidth - margin, position().y));
            }
        }

        void Player::update(const sf::Time& dt) {
            applyAcceleration(dt);
            applySpeed(dt);
            applyBulletTimeout(dt);
            clampHorizontalPosition();
            publish(EntityMessage(position(), typeid(Player)));
        }

        void Player::shot() {
            destroy();
            publish(ExplosionMessage(position()));
            publish(GameOverMessage());
        }

        void Player::setHorizontalAcceleration(const float a) {
            haccel = a;
        }

        void Player::shoot() {
            if (bulletTimeout > sf::Time::Zero)
                return;

            sf::Vector2f bulletPos = position() + sf::Vector2f(0.0f, -size * 0.6f);
            spawn(std::make_shared<PlayerBullet>(bulletPos));
            bulletTimeout = sf::seconds(0.3f);
        }
    }
}