#pragma once
#include <SFML/System/Vector2.hpp>
#include <SFML/System.hpp>
#include "observer.h"
#include "message.h"

namespace si {
    namespace model {
        /// An abstract class for game entities.
        class Entity : public virtual Observable<Message> {
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

        /// An entity that has an (x, y) position and a size: it is "physical"
        /// in that it represent some concrete being like the player or a
        /// bullet, as opposed to being an abstract container for other entities
        /// or logic. Positions and size are stored in pixels; the window size is
        /// defined in `constants.h`. For collision purposes, the "shape" of all
        /// PhysicalEntity objects is circular, centered at `position` with
        /// diameter `size`.
        class PhysicalEntity : public Entity {
        public:
            PhysicalEntity(const sf::Vector2f &p, float size);

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
            float distance(const PhysicalEntity &other) const;

            /// Determine whether or not this entity is touching a given other
            /// entity. Returns `true` if their collision circles overlap.
            bool collides(const PhysicalEntity &other) const;

            /// Determine whether or not this entity is off-screen.
            bool offScreen() const;

            /// Destroy itself, and publish an explosion message for the view.
            void explode();

        private:
            sf::Vector2f m_position;
            float m_size;
        };

        /// An interface for entities that may be shot by the player.
        class IPlayerBulletTarget {
        public:
            virtual ~IPlayerBulletTarget() {}
            virtual void shotByPlayer() = 0;
        };

        /// An interface for entities that may be shot by the enemies.
        class IEnemyBulletTarget {
        public:
            virtual ~IEnemyBulletTarget() {}
            virtual void shotByEnemy() = 0;
        };

        template <typename T>
        class Spawns {
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

        class PathedEntity : public PhysicalEntity {
        public:
            PathedEntity(const sf::Vector2f &p, float size);

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