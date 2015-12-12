#pragma once
#include <SFML/System/Vector2.hpp>
#include <SFML/System.hpp>
#include <functional>
#include "observer.h"

namespace si {
    namespace model {
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
            std::vector<std::shared_ptr<Entity>> m_siblings;
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
            IPhysical(const sf::Vector2f &p, float size);

            /// Get the entity's position.
            sf::Vector2f position() const;

            /// Get the entity's size.
            float size() const;

            /// Move to a given position.
            void moveTo(const sf::Vector2f &p);

            /// Add a given position vector to the current position.
            void moveBy(const sf::Vector2f &p);

            /// Get the distance (in pixels) to some other position.
            float distance(const sf::Vector2f &p) const;

            /// Get the distance (in pixels) to some other positioned entity.
            float distance(const IPhysical &other) const;

            /// Determine whether or not this entity is touching a given other
            /// entity. Returns `true` if their collision circles overlap.
            bool collides(const IPhysical &other) const;

            /// Determine whether or not to check collisions with the player.
            bool checkPlayerCollision() const { return false; }

            /// Determine whether or not to check collisions with invaders.
            bool checkInvaderCollision() const { return false; }

            /// Determine whether or not this entity is off-screen.
            bool offScreen() const;

        private:
            sf::Vector2f m_position;
            float m_size;
        };

        /// An interface for entities that may be shot by the player.
        class IPlayerBulletTarget {
        public:
            virtual ~IPlayerBulletTarget() {}
            virtual void shot() = 0;
        };

        /// An interface for entities that may be shot by the enemies.
        class IEnemyBulletTarget {
        public:
            virtual ~IEnemyBulletTarget() {}
            virtual void shot() = 0;
        };

        template <typename T>
        class ISpawns {
        public:
            /// Spawn a sibling entity. The parent should poll for these.
            void spawn(std::shared_ptr<T> t) {
                spawns.emplace_back(t);
            }

            /// Get a copy of this entity's spawned newSpawns and clear the cache.
            std::vector<std::shared_ptr<T>> newSpawns() {
                auto copy = spawns;
                spawns.clear();
                return copy;
            }

        private:
            std::vector<std::shared_ptr<T>> spawns;
        };

        class PathedEntity : public Entity, public virtual IPhysical {
        public:
            PathedEntity(const sf::Vector2f& p, float size)
                : IPhysical(p, size), origin(p), age(sf::Time::Zero) {}

            // The path's drag constant. 1.0f means "snap exactly to the path";
            // lower values drag towards it, lagging behind a little.
            virtual float pathDrag() const = 0;
            void PathedEntity::update(const sf::Time& dt) override;
            virtual sf::Vector2f path(sf::Time time) const = 0;

        protected:
            sf::Vector2f origin;

        private:
            sf::Time age;
        };
    }
}