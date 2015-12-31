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
            void display(const sf::Time &dt);
            
        private:
			/// Create a circle shape with the given center, diameter, and color.
            static sf::CircleShape makeCircle(const sf::Vector2f& p, float diameter, sf::Color color);

			/// Clamp a float to [0, 1] and map it to the [0x00..0xFF] range.
			static unsigned char floatByte(float x);

			/// Create a title text, centered in this view's window at the given height.
			sf::Text title(std::string s, float y) const;
			
			/// Spawn a bunch of explosion particles at the given position.
			void explode(sf::Vector2f position, int num = 50);
            void onEvent(const Message&) override;
            sf::RenderWindow &window;
            std::vector<std::shared_ptr<Particle>> particles;
            std::vector<std::shared_ptr<sf::Drawable>> drawables;

			std::vector<float> titleScreenOptionCenters;
			bool drawTitleScreen;
			sf::Time titleScreenAge;
			TitleScreenOption selectedTitleScreenOption;
			std::vector<float> titleScreenOptionFaders;

            sf::Font regularFont;
			sf::Font boldFont;
        };
    }
}