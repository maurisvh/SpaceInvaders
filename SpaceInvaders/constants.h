#pragma once
#include <SFML/Graphics.hpp>

const float pi = 3.14159265358979323f;
namespace angle {
    const float right = 0.0f * pi;
    const float down  = 0.5f * pi;
    const float left  = 1.0f * pi;
    const float up    = 1.5f * pi;
}

namespace si {
    namespace model {
        const unsigned int screenWidth = 600;
        const unsigned int screenHeight = 400;
    }

    namespace view {
        // The default background color.
        const sf::Color colSpace{10, 0, 10};
    }
}
