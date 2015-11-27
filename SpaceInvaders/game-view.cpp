#include <SFML/Graphics.hpp>
#include "game-view.h"
#include "constants.h"
#include <iostream>
#include "invader.h"
#include "player.h"

namespace si {
    namespace view {
        GameView::GameView(sf::RenderWindow &w) : window(w) {
            // backgroundStars = std::vector<BackgroundStar>(300);
            particles = std::vector<std::shared_ptr<Particle>>();
            for (int i = 0; i < 300; i++) {
                particles.emplace_back(std::make_shared<BackgroundStar>());
            }
            vgaFont.loadFromFile("vga.ttf");
        }

        void GameView::drawCircle(const sf::Vector2f &p, float diameter, sf::Color color) {
            sf::CircleShape shape{ diameter * 0.5f };
            shape.setFillColor(color);
            shape.setPosition(floor(p.x) - diameter * 0.5f,
                              floor(p.y) - diameter * 0.5f);
            window.draw(shape);
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

            for (const auto &p : invaderPositions) {
                drawCircle(p, model::Invader::size, sf::Color::Cyan);
            }   
            invaderPositions.clear();
            
            for (const auto &p : playerPositions)
                drawCircle(p, model::Player::size, sf::Color::Yellow);
            playerPositions.clear();
            
            auto bulletCount = 0;
            for (const auto &p : playerBulletPositions) {
                drawCircle(p, model::Bullet::size, sf::Color(255, 200, 50));
                ++bulletCount;
            }
            playerBulletPositions.clear();

            int fps = int(1.0f / dt.asSeconds());
            sf::Text fpsText = sf::Text(std::to_string(fps) + " fps", vgaFont, 16);
            fpsText.setPosition(5.0f, 0.0f);
            fpsText.setColor(fps < 60 ? sf::Color::Red : sf::Color::White);
            window.draw(fpsText);

            sf::Text bulletText = sf::Text(std::to_string(bulletCount) + " bullets", vgaFont, 16);
            bulletText.setPosition(5.0f, 20.0f);
            bulletText.setColor(sf::Color::White);
            window.draw(bulletText);

            window.display();
        }

        void GameView::explode(sf::Vector2f position) {
            for (int i = 0; i < 50; i++)
                particles.emplace_back(std::make_shared<ExplosionParticle>(position));
        }

        void GameView::onEvent(const model::Entity &e) {
            if (auto *i = dynamic_cast<const model::Invader*>(&e)) {
                if (i->isDestroyed())
                    explode(i->position());
                else
                    invaderPositions.emplace_back(i->position());
                
            } else if (auto *p = dynamic_cast<const model::Player*>(&e)) {
                playerPositions.emplace_back(p->position());
            } else if (auto *pb = dynamic_cast<const model::PlayerBullet*>(&e)) {
                playerBulletPositions.emplace_back(pb->position());
            }
        }
    }
}