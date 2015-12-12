#include "entity.h"
#include <cmath>
#include "constants.h"

namespace si {
    namespace model {
        Entity::Entity() : destroyed(false) {}
        void Entity::destroy() { destroyed = true; }
        bool Entity::isDestroyed() const { return destroyed; }

        IPhysical::IPhysical(const sf::Vector2f& p, float s)
            : m_position(p), m_size(s) {}

        sf::Vector2f IPhysical::position() const {
            return m_position;
        }

        float IPhysical::size() const {
            return m_size;
        }

        void IPhysical::moveTo(const sf::Vector2f& p) {
            m_position = p;
        }

        void IPhysical::moveBy(const sf::Vector2f& p) {
            m_position += p;
        }

        float IPhysical::distance(const sf::Vector2f& p) const {
            return hypot(p.x - position().x, p.y - position().y);
        }

        float IPhysical::distance(const IPhysical& other) const {
            return distance(other.position());
        }

        bool IPhysical::collides(const IPhysical& other) const {
            return distance(other) <= 0.5f * (size() + other.size());
        }

        bool IPhysical::offScreen() const {
            return (position().x < -size()
                    || position().x > screenWidth + size()
                    || position().y < -size()
                    || position().y > screenHeight + size());
        }

        void PathedEntity::update(const sf::Time& dt) {
            age += dt;
            auto delta = path(age) - position();
            moveBy((1.0f - powf(pathDrag(), dt.asSeconds())) * delta);
        }
    }
}