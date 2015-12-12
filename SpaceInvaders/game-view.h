#pragma once
#include "entity.h"
#include "observer.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include "constants.h"
#include "random.h"
#include "particle.h"
#include "message.h"


namespace si {
    namespace view {
        class GameView : public virtual Observer<Message> {
        public:
            explicit GameView(sf::RenderWindow &w);
            static sf::CircleShape makeCircle(const sf::Vector2f& p, float diameter, sf::Color color);
            void display(const sf::Time &dt);
            
        private:
            void explode(sf::Vector2f position);
            void onEvent(const Message&) override;
            sf::RenderWindow &window;
            std::vector<std::shared_ptr<Particle>> particles;
            std::vector<std::shared_ptr<sf::Drawable>> drawables;

            bool gameOver;
            sf::Font vgaFont;
            
        };
    }
}