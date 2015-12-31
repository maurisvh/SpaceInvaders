#include "particle.h"

namespace si {
    namespace view {
        Particle::Particle(sf::Vector2f position, float angle, float speed,
                           bool eternal, sf::Time lifetime,
                           sf::Color color, float size)
        : position(position), angle(angle), speed(speed),
          eternal(eternal), lifetime(lifetime), initialLifetime(lifetime), destroyed(false),
          color(color), size(size) {}

        void Particle::update(const sf::Time& dt) {
            position.x += cosf(angle) * speed * dt.asSeconds();
            position.y += sinf(angle) * speed * dt.asSeconds();

            if (!eternal) {
                lifetime -= dt;
                if (lifetime <= sf::Time::Zero)
                    destroyed = true;

                float f = (initialLifetime - lifetime).asSeconds() / initialLifetime.asSeconds();
                color.a = unsigned char((1.0f - f) * 250.0f + 2.0f);
                speed *= powf(0.5f, dt.asSeconds());
            }
        }

        void Particle::draw(sf::RenderWindow& window) {
            sf::CircleShape shape{ size * 0.5f };
            shape.setFillColor(color);
            shape.setPosition(floor(position.x) - size * 0.5f,
                              floor(position.y) - size * 0.5f);
            window.draw(shape);
        }

        BackgroundStar::BackgroundStar()
        : Particle(
              sf::Vector2f(RandomGenerator::rg.random() * float(model::screenWidth),
                           RandomGenerator::rg.random() * float(model::screenHeight)),
              angle::right,
              RandomGenerator::rg.random(5.0f, 35.0f),
              true, sf::Time(),
              sf::Color(255, 255, 255, unsigned char(RandomGenerator::rg.random(10.0f, 40.0f))),
              RandomGenerator::rg.random(2.0f, 4.0f)
          ) {}

        void BackgroundStar::update(const sf::Time& dt) {
            Particle::update(dt);
            position.x = fmodf(position.x, float(model::screenWidth));
        }

        sf::Color ExplosionParticle::fireColor() {
            float x = RandomGenerator::rg.random(0.5f, 1.0f);
            float r = x;
            float g = x * x;
            float b = 0.4f;
            return sf::Color(unsigned char(r * 255.0f),
                             unsigned char(g * 255.0f),
                             unsigned char(b * 255.0f), 255);
        }

        ExplosionParticle::ExplosionParticle(const sf::Vector2f position)
        : Particle(
              position,
              RandomGenerator::rg.random(0.0f, 2.0f * pi),
              RandomGenerator::rg.random(20.0f, 120.0f),
              false, sf::seconds(RandomGenerator::rg.random(0.5f, 2.5f)),
              fireColor(),
              RandomGenerator::rg.random(6.0f, 19.0f)
          ) {}
    }
}