#include "shield.h"
#include "message.h"
#include "logging.h"

namespace si {
    namespace model {
        const float Shield::size = 20.0f;

        Shield::Shield(sf::Vector2f p, int h)
            : PhysicalEntity(p, size), m_health(h) {
			info("Shield");
        }

		int Shield::health() const {
            return m_health;
        }

        void Shield::update(const sf::Time& dt) {
            publish(ShieldMessage(position(), health()));
        }

        void Shield::shot() {
            if (--m_health <= 0) {
                destroy();
                publish(ExplosionMessage(position()));
            }
        }

        void Shield::shotByPlayer() { shot(); }
        void Shield::shotByEnemy() { shot(); }
    }
}
