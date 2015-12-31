#include <SFML/Graphics.hpp>
#include "game-view.h"
#include "constants.h"
#include <iostream>
#include "invader.h"
#include "player.h"
#include "shield.h"

const std::string boldFontPath = "Lato-Black.ttf";
const std::string regularFontPath = "Lato-Regular.ttf";

namespace si {
    namespace view {
		sf::Text GameView::title(std::string s, float y) const {
			sf::Text text(s, boldFont, 50);
			float cx = model::screenWidth / 2.0f - text.getLocalBounds().width / 2.0f;
			text.setPosition(cx, y);
			return text;
		}

		GameView::GameView(sf::RenderWindow &w) : window(w) {
			// Always display a particle starfield.
            particles = std::vector<std::shared_ptr<Particle>>();
            for (int i = 0; i < 300; i++) {
                particles.emplace_back(std::make_shared<BackgroundStar>());
            }

			// Load some fonts.
			boldFont.loadFromFile(boldFontPath);
			regularFont.loadFromFile(regularFontPath);

			// Calculate how to space out the options on the title screen.
			std::vector<float> optionWidths;
			float s = model::screenWidth;
			for (int i = 0; i < nrTitleScreenOptions; i++) {
				titleScreenOptionFaders.push_back(0.0f);
				sf::Text t(titleScreenOptionText[i], regularFont, 20);
				float width = float(t.getLocalBounds().width);
				optionWidths.push_back(width);
				s -= width;
			}
			s /= (float(nrTitleScreenOptions) + 1.0f);
			
			// Initialize screen-specific fields.
			drawTitleScreen = false;
			selectedTitleScreenOption = StartGame;
			titleScreenOptionCenters = std::vector<float>({ s });
			for (int i = 0; i < nrTitleScreenOptions - 1; i++) {
				float prev = titleScreenOptionCenters[i];
				titleScreenOptionCenters.push_back(prev + optionWidths[i] + s);
			}
        }

        sf::CircleShape GameView::makeCircle(const sf::Vector2f &p, float diameter, sf::Color color) {
            sf::CircleShape shape{ diameter * 0.5f };
            shape.setFillColor(color);
			shape.setPosition(floor(p.x) - diameter * 0.5f, floor(p.y) - diameter * 0.5f);
            return shape;
        }

	    unsigned char GameView::floatByte(float x) {
			return unsigned char(std::max(0.0f, std::min(255.0f, x * 255.0f)));
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
            sf::Text fpsText = sf::Text(std::to_string(fps) + " fps", regularFont, 16);
            fpsText.setPosition(5.0f, 0.0f);
            fpsText.setColor(fps < 60 ? sf::Color::Red : sf::Color::White);
            window.draw(fpsText);

			if (drawTitleScreen) {
				// The title text fades in first, then the options.
				sf::Uint8 alphaTitle = floatByte(titleScreenAge.asSeconds() - 1.0f);
				sf::Uint8 alphaOptions = floatByte(titleScreenAge.asSeconds() - 2.0f);
				
				auto titleText = title("Space Invaders", 100.f);
				titleText.setColor(sf::Color(0xFF, 0xFF, 0xFF, alphaTitle));
				window.draw(titleText);

				int index = 0;
				for (auto &s : { L"  ←↑→↓", L"Move",
					             L"X     ", L"Select, Fire",
					             L"R     ", L"Reset" }) {
					auto helpText = sf::Text(s, regularFont, 16);
					const float cx = model::screenWidth / 2.f;
					const float y = 180.f + (index / 2) * 20.f;
					const float x = (index++ % 2 == 0)
									? cx - helpText.getLocalBounds().width - 15.f
									: cx + 15.f;
					helpText.setPosition(x, y);
					helpText.setColor(sf::Color(150, 150, 180, alphaOptions));
					window.draw(helpText);
				}

				for (int i = 0; i < nrTitleScreenOptions; i++) {
					bool selected = TitleScreenOption(i) == selectedTitleScreenOption;
					
					// Adjust the color faders. When an option is selected, it becomes brighter.
					// When it is deselected, it starts fading out.
					titleScreenOptionFaders[i] += (selected ? 4.0f : -4.0f) * dt.asSeconds();
					titleScreenOptionFaders[i] = std::max(0.0f, std::min(1.0f, titleScreenOptionFaders[i]));

					auto text = sf::Text(titleScreenOptionText[i], regularFont, 20);
					const auto offColor = sf::Vector3f(100.f, 100.f, 150.f);
					const auto onColor = sf::Vector3f(250.f, 250.f, 100.f);
					const auto col = offColor + (onColor - offColor) * titleScreenOptionFaders[i];
					text.setColor(sf::Color(sf::Uint8(col.x), sf::Uint8(col.y), sf::Uint8(col.z), alphaOptions));
					text.setPosition(titleScreenOptionCenters[i], 280.0f);
					window.draw(text);
				}
				drawTitleScreen = false;
			}

            window.display();
        }

        void GameView::explode(sf::Vector2f position, int num) {
            while (num-- > 0)
                particles.emplace_back(std::make_shared<ExplosionParticle>(position));
        }

        void GameView::onEvent(const Message &m) {
            if (auto d = dynamic_cast<const BulletMessage*>(&m)) {
                drawables.push_back(
                    std::make_shared<sf::CircleShape>(
                        makeCircle(d->position, model::Bullet::size, sf::Color::Red)));
            } else if (auto d = dynamic_cast<const PlayerMessage*>(&m)) {
				const auto playerColor = sf::Color(40, 170, 200);
				auto r = std::make_shared<sf::RectangleShape>(sf::Vector2f(model::screenWidth, 1.0f));
				r->setPosition(0.0f, d->position.y);
				r->setFillColor(sf::Color(playerColor.r, playerColor.g, playerColor.b, 50));
				drawables.push_back(r);
                drawables.push_back(
                    std::make_shared<sf::CircleShape>(
                        makeCircle(d->position, model::Player::size, playerColor)));
            } else if (auto d = dynamic_cast<const InvaderMessage*>(&m)) {
                drawables.push_back(
                    std::make_shared<sf::CircleShape>(
                        makeCircle(d->position, model::Invader::size,
                            sf::Color(200, 60, std::min(255, 10 + d->health * 30)))));
				drawables.push_back(
					std::make_shared<sf::CircleShape>(
						makeCircle(d->position,
							model::Invader::size * 0.6f,
							sf::Color(255, 255, 255, 100))));
			} else if (auto d = dynamic_cast<const ShieldMessage*>(&m)) {
				drawables.push_back(
                    std::make_shared<sf::CircleShape>(
                        makeCircle(d->position, model::Shield::size,
                            sf::Color(0, std::min(255, 100 + d->health * 10), 100))));
			} else if (auto d = dynamic_cast<const PopupMessage*>(&m)) {
				drawables.push_back(
					std::make_shared<sf::Text>(
						title(d->text, 120.f)));
			} else if (auto d = dynamic_cast<const ExplosionMessage*>(&m)) {
                explode(d->position);
            } else if (auto d = dynamic_cast<const TitleScreenMessage*>(&m)) {
				drawTitleScreen = true;
				titleScreenAge = d->age;
				selectedTitleScreenOption = d->option;
            }
        }
    }
}