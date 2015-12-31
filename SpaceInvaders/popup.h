#pragma once
#include "entity.h"

namespace si {
	namespace model {
		class Popup : public Entity {
		public:
			Popup(std::string text, sf::Time duration);
			void update(const sf::Time &dt) override;
		private:
			std::string text;
			sf::Time duration;
		};
	}
}
