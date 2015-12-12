#include "scene.h"
#include "constants.h"
#include "bullet.h"
#include <algorithm>

namespace si {
    namespace model {
        Scene::Scene() {
            for (int x = -2; x <= 2; x++) {
                for (int y = 0; y < 3; y++) {
                    sf::Vector2f pos = sf::Vector2f(screenWidth / 2.0f + 60.0f * x - 112.5f, 50.0f + 60.0f * y);
                    invaders.push_back(std::make_shared<Invader>(pos));
                }
            }

            sf::Vector2f playerPosition(screenWidth / 2.0f, screenHeight - 40.0f);
            players = std::vector<std::shared_ptr<Player>>({
                std::make_shared<Player>(playerPosition),
            });
        }

        void Scene::observeChildren() {
            for (auto &e : players)
                e->addObserver(shared_from_this());
            for (auto &e : invaders)
                e->addObserver(shared_from_this());
        }

        template <typename E>
        void eraseDestroyed(std::vector<std::shared_ptr<E>> &entities) {
            entities.erase(
                std::remove_if(entities.begin(), entities.end(),
                [](std::shared_ptr<E> e) { return e->isDestroyed(); }),
                entities.end());
        }

        void Scene::update(const sf::Time &dt) {
            eraseDestroyed(players);
            for (auto &e : players) {
                e->update(dt);
                for (auto b : e->newSpawns()) {
                    playerBullets.push_back(b);
                    b->addObserver(shared_from_this());
                }
            }
            
            eraseDestroyed(invaders);
            for (auto &e : invaders) {
                e->update(dt);
                for (auto b : e->newSpawns()) {
                    enemyBullets.push_back(b);
                    b->addObserver(shared_from_this());
                }
            }

            eraseDestroyed(playerBullets);
            for (auto &e : playerBullets) {
                e->update(dt);
                for (auto &other : invaders)
                    if (e->collides(*other))
                        e->hitEnemy(*other);
            }

            eraseDestroyed(enemyBullets);
            for (auto &e : enemyBullets) {
                e->update(dt);
                for (auto &other : players)
                    if (e->collides(*other))
                        e->hitPlayer(*other);
            }
        }

        void Scene::keyEvent(const controller::KeyEvent e) {
            if (e.key == controller::GoLeft) {
                setPlayerAcceleration(-400.0f);
            }
            if (e.key == controller::GoRight) {
                setPlayerAcceleration(+400.0f);
            }
            if (e.key == controller::Shoot) {
                playerShoot();
            }
        }

        void Scene::setPlayerAcceleration(float h) {
            for (auto &e : players)
                e->setHorizontalAcceleration(h);
        }

        void Scene::playerShoot() {
            for (auto &e : players)
                e->shoot();
        }
    }
}