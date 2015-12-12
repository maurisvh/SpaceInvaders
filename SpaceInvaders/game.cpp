#include "game.h"

namespace si {
    namespace model {
        Game::Game() {
            scenes = std::vector<std::shared_ptr<Scene>>({
                std::make_shared<Scene>()
            });
        }

        void Game::observeChildren() {
            for (auto &s : scenes) {
                s->observeChildren();
                s->addObserver(shared_from_this());
            }
        }

        void Game::update(const sf::Time &dt) {
            for (auto &s : scenes)
                s->update(dt);
        }

        void Game::onEvent(const controller::KeyEvent &e) {
            if (e.key == controller::DebugRestart) {
                scenes = std::vector<std::shared_ptr<Scene>>({
                    std::make_shared<Scene>()
                });
                observeChildren();
                publish(GameStartMessage());
                return;
            }

            for (auto &s : scenes)
                s->keyEvent(e);
        }
    }
}