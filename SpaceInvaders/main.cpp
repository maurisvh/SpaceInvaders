#include <SFML/Graphics.hpp>
#include <iostream>
#include "constants.h"
#include "game.h"
#include "timing.h"
#include "random.h"
#include "game-view.h"
#include <memory>
#include "controller.h"

namespace si {
    void playGame() {
        Stopwatch &sw = Stopwatch::instance;
        RandomGenerator &rg = RandomGenerator::rg;

        sf::RenderWindow window{
            sf::VideoMode(model::screenWidth, model::screenHeight),
            "Space Invaders",
            sf::Style::Close | sf::Style::Titlebar};

        auto game = std::make_shared<model::Game>();
        game->observeChildren();

        auto gameView = std::make_shared<view::GameView>(window);
        game->addObserver(gameView);

        controller::Controller controller;
        controller.registerGame(game);

        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    window.close();
            }
            
            sf::Time dt = sw.getDelta();
            controller.poll(dt);
            game->update(dt);
            gameView->display(dt);
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
    return 0;
}
