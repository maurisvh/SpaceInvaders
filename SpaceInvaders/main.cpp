#include <SFML/Graphics.hpp>
#include <iostream>
#include "constants.h"
#include "game.h"
#include "timing.h"
#include "random.h"

namespace si {
    void playGame() {
        sf::RenderWindow window(
            sf::VideoMode(screen_width, screen_height),
            "Space Invaders",
            sf::Style::Close | sf::Style::Titlebar);
        
        // sf::CircleShape shape(100.0);
        // shape.setFillColor(sf::Color::Green);

        Stopwatch &sw = Stopwatch::instance();
        RandomGenerator &rg = RandomGenerator::instance();

        model::Game game;
        
        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    window.close();
            }
            
            sf::Time dt = sw.getDelta();
            game.update(dt);

            window.clear(col_space);
            window.display();
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
