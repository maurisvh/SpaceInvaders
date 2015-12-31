#include "popup.h"

namespace si {
	namespace model {
		Popup::Popup(std::string text, sf::Time duration)
			: text(text), duration(duration) {}

		void Popup::update(const sf::Time &dt) {
			duration -= dt;
			if (duration <= sf::Time::Zero)
				destroy();
			else
				publish(PopupMessage(text));
		}
	}
}