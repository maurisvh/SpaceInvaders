#include "random.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include "constants.h"

namespace si {
    namespace view {
        /// A tiny moving circle that maybe self-destructs after some time.
        struct Particle {
            virtual ~Particle() {}

            /// Create a new particle at the given position.
            Particle(sf::Vector2f position, float angle, float speed,
                     bool eternal, sf::Time lifetime,
                     sf::Color color, float size);

            /// Move and update this particle's lifetime.
            void virtual update(const sf::Time &dt);

            /// Draw this particle to the given window.
            void draw(sf::RenderWindow &window);

            sf::Vector2f position;
            float angle;
            float speed;
            bool eternal;
            sf::Time lifetime;
            sf::Time initialLifetime;
            bool destroyed;
            sf::Color color;
            float size;
        };

        /// A star that moves horizontally and wraps around the screen.
        struct BackgroundStar : Particle {
            BackgroundStar();
            void virtual update(const sf::Time &dt) override;
        };

        /// A flame particle that moves in a random direction and dies out quickly.
        struct ExplosionParticle : Particle {
            /// A random red-orangey color for explosion particles.
            sf::Color fireColor();
            explicit ExplosionParticle(const sf::Vector2f position);
        };
    }
}