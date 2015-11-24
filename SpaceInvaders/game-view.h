#pragma once
#include "entity.h"
#include "observer.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include "constants.h"
#include "random.h"


namespace si {
    namespace view {
        struct BackgroundStar {
            BackgroundStar() :
                position(RandomGenerator::rg.random() * float(model::screenWidth),
                         RandomGenerator::rg.random() * float(model::screenHeight)),
                hspeed(5.0f + RandomGenerator::rg.random() * 30.0f),
                color(255, 255, 255, unsigned char(RandomGenerator::rg.random() * 30.0f + 10.0f)),
                size(2.0f + RandomGenerator::rg.random() * 2.0f) {}

            void update(const sf::Time &dt) {
                position.x += hspeed * dt.asSeconds();
                position.x = fmodf(position.x, float(model::screenWidth));
            }

            sf::Vector2f position;
            float hspeed;
            sf::Color color;
            float size;
        };

        class GameView : public virtual Observer<model::Entity> {
        public:
            explicit GameView(sf::RenderWindow &w);
            void drawCircle(const sf::Vector2f& p, float diameter, sf::Color color);
            void display(const sf::Time &dt);
            
        private:
            void onEvent(const model::Entity&) override;
            sf::RenderWindow &window;
            std::vector<BackgroundStar> backgroundStars;
            std::vector<sf::Vector2f> invaderPositions;
            std::vector<sf::Vector2f> playerPositions;
            std::vector<sf::Vector2f> playerBulletPositions;
            sf::Font vgaFont;
        };
    }
}