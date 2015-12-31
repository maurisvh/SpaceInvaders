#include "title-screen.h"
#include "logging.h"

namespace si {
	namespace model {
		TitleScreen::TitleScreen() : optionIndex(0) {
			info("Created the title screen.");
		}

		sf::Time TitleScreen::age() const {
			return m_age;
		}

		TitleScreenOption TitleScreen::option() const {
			return TitleScreenOption(optionIndex);
		}

		void TitleScreen::previousOption() {
			if (optionIndex == 0)
				optionIndex = nrTitleScreenOptions - 1;
			else
				optionIndex--;
		}

		void TitleScreen::nextOption() {
			if (optionIndex == nrTitleScreenOptions - 1)
				optionIndex = 0;
			else
				optionIndex++;
		}

		void TitleScreen::update(const sf::Time &dt) {
			m_age += dt;
			publish(TitleScreenMessage(m_age, option()));
		}

		void TitleScreen::keyAction(const controller::KeyAction e) {
			if (e == controller::MenuLeft) {
				previousOption();
			} else if (e == controller::MenuRight) {
				nextOption();
			}
		}
	}
}
