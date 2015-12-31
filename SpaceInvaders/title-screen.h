#pragma once
#include <SFML/System/Time.hpp>
#include "entity.h"
#include "key-event.h"

namespace si {
	namespace model {
		class TitleScreen : public Entity {
		public:
			TitleScreen();
			
			void update(const sf::Time &dt) override;
			void keyAction(const controller::KeyAction e);

			sf::Time age() const;
			TitleScreenOption option() const;

			void previousOption();
			void nextOption();
		private:
			sf::Time m_age;
			int optionIndex;
		};
	}
}
