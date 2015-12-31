#pragma once
#include <SFML/System/Vector2.hpp>
#include <typeinfo>
#include "title-screen-option.h"

namespace si {
    struct Message { virtual ~Message() {}; };

	struct TitleScreenMessage : Message {
		TitleScreenMessage(const sf::Time &a, TitleScreenOption o) : age(a), option(o) {}
		sf::Time age; TitleScreenOption option;
	};
    
	struct GameStartMessage : Message {};
    
	struct GameOverMessage : Message {};
    
	struct ExplosionMessage : Message {
        explicit ExplosionMessage(sf::Vector2f p) : position(p) {}
        sf::Vector2f position;
    };

	struct BulletMessage : Message {
		explicit BulletMessage(sf::Vector2f p) : position(p) {}
		sf::Vector2f position;
	};

	struct InvaderMessage : Message {
		explicit InvaderMessage(sf::Vector2f p, int h) : position(p), health(h) {}
		sf::Vector2f position;
		int health;
	};

	struct PlayerMessage : Message {
		explicit PlayerMessage(sf::Vector2f p) : position(p) {}
		sf::Vector2f position;
	};

	struct ShieldMessage : Message {
		explicit ShieldMessage(sf::Vector2f p, int h) : position(p), health(h) {}
		sf::Vector2f position;
		int health;
	};

	struct PopupMessage : Message {
		explicit PopupMessage(std::string t) : text(t) {}
		std::string text;
	};
}
