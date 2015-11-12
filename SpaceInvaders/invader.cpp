#include "invader.h"
#include <iostream>

namespace si {
    namespace model {
        const double Invader::size = 30.0;

        Invader::Invader(const sf::Vector2f& p)
            : IPhysical(p, size) {}

        void Invader::update(const sf::Time &dt) {
            moveBy(sf::Vector2f(30.0 * dt.asSeconds(), 0.0));
            std::cout << position().x << std::endl;
        }
    }
}