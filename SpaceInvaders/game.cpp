#include "game.h"
#include "read-level.h"

namespace si {
    namespace model {
        Game::Game() : m_quitting(false) {
			titleScreen = TitleScreen();
        }

        void Game::observeChildren() {
			if (titleScreen)
				titleScreen->addObserver(this);
			if (scene) {
				scene->observeChildren();
				scene->addObserver(this);
			}
        }

		void Game::update(const sf::Time &dt) {
			if (titleScreen)
				titleScreen->update(dt);
			if (scene) {
				scene->update(dt);
				if (scene->finished()) {
					if (scene->state() == Scene::State::GameOver)
						levelBuffer.clear();
					nextLevel();
				}
			}
		}

		void Game::onEvent(const Message& m) {
            publish(m);
        }

        void Game::onEvent(const controller::KeyAction &act) {
			if (act == controller::DebugRestart) {
				titleScreen = TitleScreen();
				scene = {};
                observeChildren();
                publish(GameStartMessage());
                return;
            }

			if (act == controller::MenuSelect) {
				if (titleScreen) {
					if (titleScreen->option() == StartGame) {
						levelBuffer = readLevels();
						levelNumber = 1;
						nextLevel();
					} else if (titleScreen->option() == QuitGame) {
						m_quitting = true;
					}
				}
				titleScreen = {};
			}

			if (titleScreen)
				titleScreen->keyAction(act);
            if (scene)
				scene->keyAction(act);
        }

		void Game::nextLevel() {
			if (levelBuffer.empty()) {
				// Return to the title screen.
				scene = {};
				titleScreen = TitleScreen();
				titleScreen->addObserver(this);
			} else {
				// Load the next level.
				scene = Scene(levelBuffer.front(), levelNumber++);
				levelBuffer.pop_front();
				scene->observeChildren();
				scene->addObserver(this);
			}
		}

		bool Game::quitting() const {
			return m_quitting;
        }

	    bool Game::playing() const {
			return bool(scene);
        }
    }
}
