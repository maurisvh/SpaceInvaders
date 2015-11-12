#pragma once
#include <SFML/System/Vector2.hpp>
#include <SFML/System.hpp>

namespace si {
    /// An abstract class for game entities.
    class Entity {
    public:
        Entity();

        /// Mark this entity as destroyed. It will be removed from the model
        /// and deleted at the end of the current tick.
        void destroy();

        /// Is this entity destroyed?
        bool isDestroyed() const;

        /// Sent to each entity once per tick. The argument is the time passed
        /// since the last tick.
        virtual void update(const sf::Time &dt) = 0;

        virtual ~Entity() {}

    private:
        bool destroyed;
    };

    /// An interface for entities that have an (x, y) position and a size.
    /// That is, they represent some physical entity like the player or a
    /// bullet, as opposed to being an abstract container for other entities
    /// or logic. Positions and size are stored in pixels; the window size is
    /// defined in `constants.h`. For collision purposes, the "shape" of all
    /// IPhysical objects is circular, centered at `position` with diameter
    /// `size`.
    class IPhysical {
    public:
        IPhysical(const sf::Vector2f &p, double size);

        /// Get the entity's position.
        sf::Vector2f position() const;

        /// Get the entity's size.
        double size() const;
        
        /// Move to a given position.
        void moveTo(const sf::Vector2f &p);

        /// Add a given position vector to the current position.
        void moveBy(const sf::Vector2f &p);

        /// Get the distance (in pixels) to some other position.
        double distance(const sf::Vector2f &p) const;
        
        /// Get the distance (in pixels) to some other positioned entity.
        double distance(const IPhysical &other) const;

        /// Determine whether or not this entity is touching a given other
        /// entity. Returns `true` if their collision circles overlap.
        bool collides(const IPhysical &other) const;

    private:
        sf::Vector2f m_position;
        double m_size;
    };
}