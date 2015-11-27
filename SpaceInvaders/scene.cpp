#include "scene.h"
#include "constants.h"
#include "bullet.h"
#include <algorithm>

namespace si {
    namespace model {
        Scene::Scene() {
            invaders = std::vector<std::shared_ptr<Invader>>({
                std::make_shared<Invader>(sf::Vector2f(50, 50)),
                std::make_shared<Invader>(sf::Vector2f(110, 50)),
                std::make_shared<Invader>(sf::Vector2f(170, 50)),
                std::make_shared<Invader>(sf::Vector2f(230, 50)),
            });

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
            for (auto &e : players) {
                e->update(dt);
                for (std::shared_ptr<PlayerBullet> b : e->newSpawns()) {
                    playerBullets.push_back(b);
                    b->addObserver(shared_from_this());
                }
            }
            
            eraseDestroyed(invaders);
            for (auto &e : invaders) {
                e->update(dt);
            }

            eraseDestroyed(playerBullets);
            for (auto &e : playerBullets) {
                e->update(dt);
                for (auto &other : invaders)
                    if (e->collides(*other)) {
                        e->hit(*other);
                    }
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