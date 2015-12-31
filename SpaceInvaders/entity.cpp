#include "entity.h"
#include <cmath>
#include "constants.h"

namespace si {
    namespace model {
        Entity::Entity() : destroyed(false) {}
        void Entity::destroy() { destroyed = true; }
        bool Entity::isDestroyed() const { return destroyed; }

        PhysicalEntity::PhysicalEntity(const sf::Vector2f& p, float s)
            : Entity(), m_position(p), m_size(s) {}

        sf::Vector2f PhysicalEntity::position() const {
            return m_position;
        }

        float PhysicalEntity::size() const {
            return m_size;
        }

        void PhysicalEntity::moveTo(const sf::Vector2f& p) {
            m_position = p;
        }

        void PhysicalEntity::moveBy(const sf::Vector2f& p) {
            m_position += p;
        }

        float PhysicalEntity::distance(const sf::Vector2f& p) const {
            return hypot(p.x - position().x, p.y - position().y);
        }

        float PhysicalEntity::distance(const PhysicalEntity& other) const {
            return distance(other.position());
        }

        bool PhysicalEntity::collides(const PhysicalEntity& other) const {
            return distance(other) <= 0.5f * (size() + other.size());
        }

        bool PhysicalEntity::offScreen() const {
            return (position().x < -size()
                    || position().x > screenWidth + size()
                    || position().y < -size()
                    || position().y > screenHeight + size());
        }

        void PhysicalEntity::explode() {
            publish(ExplosionMessage(position()));
            destroy();
        }

        PathedEntity::PathedEntity(const sf::Vector2f& p, float size)
            : PhysicalEntity(p, size), origin(p), age(sf::Time::Zero) {}

        void PathedEntity::update(const sf::Time& dt) {
            age += dt;
            auto delta = path(age) - position();
            moveBy((1.0f - powf(pathDrag(), dt.asSeconds())) * delta);
        }
    }
}