#include "entity.h"
#include <cmath>

namespace si {
    Entity::Entity() : destroyed(false) {}
    void Entity::destroy() { destroyed = true; }
    bool Entity::isDestroyed() const { return destroyed; }

    IPhysical::IPhysical(const sf::Vector2f& p, double s)
        : m_position(p), m_size(s) {}

    sf::Vector2f IPhysical::position() const {
        return m_position;
    }

    double IPhysical::size() const {
        return m_size;
    }

    void IPhysical::moveTo(const sf::Vector2f& p) {
        m_position = p;
    }

    void IPhysical::moveBy(const sf::Vector2f& p) {
        m_position += p;
    }

    double IPhysical::distance(const sf::Vector2f& p) const {
        return hypot(p.x, p.y);
    }

    double IPhysical::distance(const IPhysical& other) const {
        return distance(other.position());
    }

    bool IPhysical::collides(const IPhysical& other) const {
        return distance(other) <= size() + other.size();
    }
}