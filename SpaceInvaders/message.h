#pragma once
#include <SFML/System/Vector2.hpp>
#include <typeinfo>

namespace si {
    struct Message { virtual ~Message() {}; };

    struct GameStartMessage : Message {};
    struct GameOverMessage : Message {};
    struct ExplosionMessage : Message {
        explicit ExplosionMessage(sf::Vector2f p)
            : position(p) {}
        sf::Vector2f position;
    };
    struct EntityMessage : Message {
        EntityMessage(sf::Vector2f p, const type_info &t)
            : position(p), type(t) {}
        sf::Vector2f position; const type_info &type;
    };
    struct HealthEntityMessage : Message {
        HealthEntityMessage(sf::Vector2f p, int h, const type_info &t)
            : position(p), health(h), type(t) {}
        sf::Vector2f position; int health; const type_info &type;
    };
}