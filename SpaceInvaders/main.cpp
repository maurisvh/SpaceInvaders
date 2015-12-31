#include <SFML/Graphics.hpp>
#include <iostream>
#include "constants.h"
#include "game.h"
#include "timing.h"
#include "random.h"
#include "game-view.h"
#include <memory>
#include "controller.h"
#include "logging.h"

namespace si {
    void playGame() {
        sf::RenderWindow window(
            sf::VideoMode(model::screenWidth, model::screenHeight),
            "Space Invaders",
			// Don't allow resizing the game window.
            sf::Style::Close | sf::Style::Titlebar,
			// Use 4x multi-sampled anti-aliasing.
			sf::ContextSettings(0, 0, 4));

		info("Starting game.");
        model::Game game;
        game.observeChildren();

        auto gameView = view::GameView(window);
        game.addObserver(&gameView);

        controller::Controller controller;
        controller.registerGame(&game);

        while (window.isOpen() && !game.quitting()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    window.close();
                else if (event.type == sf::Event::KeyPressed)
                    controller.press(event.key.code);
            }
            
            sf::Time dt = Stopwatch::sw.getDelta();
            controller.poll(dt);
            game.update(dt);
            gameView.display(dt);
        }
    }
}

int main() {
    try {
        si::playGame();
    }
    catch (const std::exception &e) {
        std::cerr << "Fatal error: " << e.what() << std::endl;
    }
}
