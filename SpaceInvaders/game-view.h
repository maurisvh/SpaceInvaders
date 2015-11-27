#pragma once
#include "entity.h"
#include "observer.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include "constants.h"
#include "random.h"


namespace si {
    namespace view {
        struct Particle {
            virtual ~Particle() {}

            Particle(sf::Vector2f position, float angle, float speed,
                     bool eternal, sf::Time lifetime,
                     sf::Color color, float size)
            : position(position), angle(angle), speed(speed), 
              eternal(eternal), lifetime(lifetime), initialLifetime(lifetime), destroyed(false),
              color(color), size(size) {}

            void virtual update(const sf::Time &dt) {
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

            void draw(sf::RenderWindow &window) {
                sf::CircleShape shape{ size * 0.5f };
                shape.setFillColor(color);
                shape.setPosition(floor(position.x) - size * 0.5f,
                                  floor(position.y) - size * 0.5f);
                window.draw(shape);
            }

            sf::Time initialLifetime;
            sf::Vector2f position; float angle; float speed;
            bool eternal; sf::Time lifetime; bool destroyed;
            sf::Color color; float size;
        };
        
        struct BackgroundStar : Particle {
            BackgroundStar() :
                Particle(
                    sf::Vector2f(RandomGenerator::rg.random() * float(model::screenWidth),
                                 RandomGenerator::rg.random() * float(model::screenHeight)),
                    angle::right,
                    5.0f + RandomGenerator::rg.random() * 30.0f,
                    true, sf::Time(),
                    sf::Color(255, 255, 255, unsigned char(RandomGenerator::rg.random() * 30.0f + 10.0f)),
                    2.0f + RandomGenerator::rg.random() * 2.0f
                ) {}

            void virtual update(const sf::Time &dt) override {
                Particle::update(dt);
                position.x = fmodf(position.x, float(model::screenWidth));
            }
        };
        
        struct ExplosionParticle : Particle {
            sf::Color fireColor() {
                float x = RandomGenerator::rg.random() * 0.5f + 0.5f;
                float r = x;
                float g = x * x;
                float b = 0.4f;
                return sf::Color(unsigned char(r * 255.0f),
                                 unsigned char(g * 255.0f),
                                 unsigned char(b * 255.0f), 255);
            }

            explicit ExplosionParticle(const sf::Vector2f position) :
            Particle(
                position,
                RandomGenerator::rg.random() * 2.0f * pi,
                20.0f + RandomGenerator::rg.random() * 100.0f,
                false, sf::seconds(0.5f + RandomGenerator::rg.random() * 2.0f),
                fireColor(),
                3.0f + RandomGenerator::rg.random() * 10.0f
            ) {}
        };

        class GameView : public virtual Observer<model::Entity> {
        public:
            explicit GameView(sf::RenderWindow &w);
            void drawCircle(const sf::Vector2f& p, float diameter, sf::Color color);
            void display(const sf::Time &dt);
            
        private:
            void explode(sf::Vector2f position);
            void onEvent(const model::Entity&) override;
            sf::RenderWindow &window;
            std::vector<sf::Vector2f> invaderPositions;
            std::vector<sf::Vector2f> playerPositions;
            std::vector<sf::Vector2f> playerBulletPositions;
            std::vector<std::shared_ptr<Particle>> particles;

            sf::Font vgaFont;
        };
    }
}