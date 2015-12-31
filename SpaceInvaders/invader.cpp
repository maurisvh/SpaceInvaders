#include "invader.h"
#include <iostream>
#include "random.h"
#include "constants.h"

namespace si {
    namespace model {
        const float Invader::size = 50.0;

        Invader::Invader(const sf::Vector2f& p, int health, sf::Time bulletPeriod)
            : PathedEntity(p, size),
              xWigglePeriod(RandomGenerator::rg.random(4.0f, 6.0f)),
              yWigglePeriod(RandomGenerator::rg.random(4.0f, 6.0f)),
              wigglePhase(RandomGenerator::rg.random(0.0f, 30.0f)),
              m_health(health),
              m_bulletPeriod(bulletPeriod) {
            setBulletTimer();
        }

        int Invader::health() const { return m_health; }

        float Invader::pathDrag() const { return 0.1f; }

        sf::Vector2f Invader::path(sf::Time time) const {
            // Zigzag right-down-left-down with a period of ten seconds.
            // The path's width is 4.5 * 50.0 = 225 pixels.

            const float v = 50.0; // speed (pixels per second)
            const float sec = time.asSeconds(); // time passed (seconds)

            const float q = floor(sec / 10.0f); // nr of periods
            const float r = fmod(sec, 10.0f);   // time in current period

            // pathOrigin = zigzag period start
            sf::Vector2f pathOrigin = q * sf::Vector2f(0.0f, v * 1.0f);
            
            // pathRel = point relative to period start
            sf::Vector2f pathRel =
                  (r < 4.5f) ? sf::Vector2f(v * r, 0.0f)
                : (r < 5.0f) ? sf::Vector2f(v * 4.5f, v * (r - 4.5f))
                : (r < 9.5f) ? sf::Vector2f(v * 4.5f - v * (r - 5.0f), v * 0.5f)
                : sf::Vector2f(0.0f, v * 0.5f + v * (r - 9.5f));
            
            // wiggle = small displacement
            sf::Vector2f wiggle =
                sf::Vector2f(sinf(sec * xWigglePeriod + wigglePhase),
                             cosf(sec * yWigglePeriod + wigglePhase)) * 5.0f;

            return origin + pathOrigin + pathRel + wiggle;
        }

        void Invader::shotByPlayer() {
            if (--m_health <= 0)
                explode();
        }

        void Invader::update(const sf::Time &dt) {
            PathedEntity::update(dt);
            m_bulletTimer -= dt;

            if (m_bulletTimer <= sf::Time::Zero) {
                float a = angle::down + RandomGenerator::rg.random(-0.3f, 0.3f);
                spawn(std::make_shared<EnemyBullet>(position(), a));
                setBulletTimer();
            }
            publish(InvaderMessage(position(), health()));
        }

        void Invader::setBulletTimer() {
            m_bulletTimer = m_bulletPeriod * RandomGenerator::rg.random(0.5f, 1.5f);
        }
    }
}