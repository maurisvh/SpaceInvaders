#include <SFML/Graphics.hpp>
#include "game-view.h"
#include "constants.h"
#include <iostream>
#include "invader.h"
#include "player.h"

namespace si {
    namespace view {
        GameView::GameView(sf::RenderWindow &w) : window(w), gameOver(false) {
            particles = std::vector<std::shared_ptr<Particle>>();
            for (int i = 0; i < 300; i++) {
                particles.emplace_back(std::make_shared<BackgroundStar>());
            }
            vgaFont.loadFromFile("vga.ttf");
        }

        sf::CircleShape GameView::makeCircle(const sf::Vector2f &p, float diameter, sf::Color color) {
            sf::CircleShape shape{ diameter * 0.5f };
            shape.setFillColor(color);
            shape.setPosition(floor(p.x) - diameter * 0.5f,
                              floor(p.y) - diameter * 0.5f);
            return shape;
        }

        void GameView::display(const sf::Time &dt) {
            window.clear(colSpace);

            // Draw the particles below everything else.
            particles.erase(
                std::remove_if(particles.begin(), particles.end(),
                    [](std::shared_ptr<Particle> p) { return p->destroyed; }),
                particles.end()
            );
            for (auto p : particles) {
                p->update(dt);
                p->draw(window);
            }

            for (const auto &d : drawables) {
                window.draw(*d);
            }
            drawables.clear();

            int fps = int(1.0f / dt.asSeconds());
            sf::Text fpsText = sf::Text(std::to_string(fps) + " fps", vgaFont, 16);
            fpsText.setPosition(5.0f, 0.0f);
            fpsText.setColor(fps < 60 ? sf::Color::Red : sf::Color::White);
            window.draw(fpsText);

            if (gameOver) {
                sf::Text gameOverText = sf::Text("GAME OVER ;_;", vgaFont, 64);
                float cx = model::screenWidth  / 2.0f - gameOverText.getLocalBounds().width / 2.0f;

                gameOverText.setPosition(cx + 2.0f, 102.0f);
                gameOverText.setColor(sf::Color::Black);
                window.draw(gameOverText);
                gameOverText.setPosition(cx - 2.0f, 98.0f);
                gameOverText.setColor(sf::Color::White);
                window.draw(gameOverText);
            }

            window.display();
        }

        void GameView::explode(sf::Vector2f position) {
            for (int i = 0; i < 50; i++)
                particles.emplace_back(std::make_shared<ExplosionParticle>(position));
        }

        void GameView::onEvent(const Message &m) {
            // TODO: specific event for entity with health?
            if (auto d = dynamic_cast<const GameStartMessage*>(&m)) {
                gameOver = false;
            } else if (auto d = dynamic_cast<const GameOverMessage*>(&m)) {
                gameOver = true;
            } else if (auto d = dynamic_cast<const EntityMessage*>(&m)) {
                if (d->type == typeid(model::Bullet)) {
                    drawables.push_back(
                        std::make_shared<sf::CircleShape>(
                            makeCircle(d->position, model::Bullet::size, sf::Color::Yellow)));
                } else if (d->type == typeid(model::Player)) {
                    drawables.push_back(
                        std::make_shared<sf::CircleShape>(
                            makeCircle(d->position, model::Player::size, sf::Color(40, 170, 200))));
                }
            } else if (auto d = dynamic_cast<const HealthEntityMessage*>(&m)) {
                if (d->type == typeid(model::Invader)) {
                    drawables.push_back(
                        std::make_shared<sf::CircleShape>(
                            makeCircle(d->position, model::Invader::size,
                                sf::Color(200, 60, 10 + d->health * 30))));
                }
            } else if (auto d = dynamic_cast<const ExplosionMessage*>(&m)) {
                explode(d->position);
            }
        }
    }
}