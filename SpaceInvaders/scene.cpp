#include "scene.h"
#include "constants.h"
#include "bullet.h"
#include <algorithm>
#include "logging.h"

namespace si {
    namespace model {
		Scene::Scene() : m_state(State::IntroCard) {}

        Scene::Scene(std::vector<std::shared_ptr<Entity>> entities,
					 optional<int> levelNumber) : Scene() {
			info("Created a new scene.");

			for (auto &e : entities) {
				if (auto i = std::dynamic_pointer_cast<Invader>(e)) {
					invaders.push_back(i);
				} else if (auto s = std::dynamic_pointer_cast<Shield>(e)) {
					shields.push_back(s);
				} else {
					throw std::runtime_error("Unhandled entity in scene creation");
				}
			}
            sf::Vector2f playerPosition(screenWidth / 2.0f, screenHeight - 40.0f);
			players.push_back(std::make_shared<Player>(playerPosition));
			
			std::string levelName = levelNumber ? "Level " + std::to_string(*levelNumber) : "Testing Level";
			popups.push_back(std::make_shared<Popup>(levelName, sf::seconds(1.5f)));
        }

		void Scene::observeChildren() {
            for (auto &e : players)  e->addObserver(this);
            for (auto &e : invaders) e->addObserver(this);
            for (auto &e : shields)  e->addObserver(this);
			for (auto &e : popups)   e->addObserver(this);
        }

        void Scene::onEvent(const Message& m) {
            publish(m);
        }

        template <typename E>
        void updateAll(std::vector<std::shared_ptr<E>> &entities, const sf::Time &dt) {
            // Erase all destroyed entities from the vector.
            entities.erase(
                std::remove_if(entities.begin(), entities.end(),
                [](std::shared_ptr<E> e) { return e->isDestroyed(); }),
                entities.end());
            
            // Update the ones that are still alive.
            for (auto &e : entities) {
                e->update(dt);
            }
        }

        template <typename E>
        void Scene::playerBulletsCollideWith(std::vector<std::shared_ptr<E>> &entities) {
            for (auto b : playerBullets)
                for (auto e : entities)
                    if (b->collides(*e))
                        b->hitEnemy(*e);
        }

        template <typename E>
        void Scene::enemyBulletsCollideWith(std::vector<std::shared_ptr<E>> &entities) {
            for (auto b : enemyBullets)
                for (auto e : entities)
                    if (b->collides(*e))
                        b->hitPlayer(*e);
        }

        void Scene::collectPlayerBullets() {
            for (auto &e : players) {
                for (auto b : e->newSpawns()) {
                    playerBullets.push_back(b);
                    b->addObserver(this);
                }
            }
        }

        void Scene::collectEnemyBullets() {
            for (auto &e : invaders) {
                for (auto b : e->newSpawns()) {
                    enemyBullets.push_back(b);
                    b->addObserver(this);
                }
            }
        }

		void Scene::invaderCollisions() {
			for (auto &i : invaders) {
				for (auto &s : shields)
					if (i->collides(*s))
						s->explode();
				for (auto &p : players)
					if (i->collides(*p) || i->position().y > p->position().y)
						p->explode();
			}
		}

	    void Scene::showPopup(const std::string str, sf::Time duration) {
			std::cerr << "showPopup " << str << std::endl;
			auto popup = std::make_shared<Popup>(str, duration);
			popups.push_back(popup);
			popup->addObserver(this);
		}

		void Scene::simulate(const sf::Time &dt) {
			updateAll(players, dt);
			updateAll(invaders, dt);
			updateAll(shields, dt);
			updateAll(playerBullets, dt);
			updateAll(enemyBullets, dt);
			updateAll(popups, dt);

			collectPlayerBullets();
			collectEnemyBullets();

			playerBulletsCollideWith(invaders);
			playerBulletsCollideWith(shields);
			enemyBulletsCollideWith(players);
			enemyBulletsCollideWith(shields);
			invaderCollisions();
		}

	    void Scene::update(const sf::Time &dt) {
			switch (m_state) {
				case State::IntroCard:
					updateAll(popups, dt);
					if (popups.empty())
						m_state = State::Playing;
					break;
				case State::Playing:
					simulate(dt);
					if (players.empty()) {
						info("Player died; game over.");
						m_state = State::GameOverCard;
						showPopup("Game Over");
					} else if (invaders.empty() && enemyBullets.empty()) {
						info("Player killed all invaders!");
						m_state = State::VictoryCard;
						showPopup("Victory!");
					}
					break;
				case State::VictoryCard:
					simulate(dt);
					if (popups.empty())
						m_state = State::Victory;
					break;
				case State::GameOverCard:
					simulate(dt); 
					if (popups.empty())
						m_state = State::GameOver;
				default:
					break;
			}
        }

        void Scene::keyAction(const controller::KeyAction act) {
            if (act == controller::GoLeft)
                setPlayerAcceleration(-400.0f);
            else if (act == controller::GoRight)
                setPlayerAcceleration(+400.0f);
            else if (act == controller::Shoot)
                playerShoot();
        }

        void Scene::setPlayerAcceleration(float h) {
            for (auto &e : players)
                e->setHorizontalAcceleration(h);
        }

        void Scene::playerShoot() {
            for (auto &e : players)
                e->shoot();
        }

	    Scene::State Scene::state() const {
			return m_state;
		}

	    bool Scene::finished() const {
			return m_state == State::GameOver || m_state == State::Victory;
		}
    }
}
