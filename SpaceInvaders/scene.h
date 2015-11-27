#pragma once
#include "entity.h"
#include <vector>
#include "invader.h"
#include "player.h"
#include "bullet.h"
#include <future>
#include "key-event.h"

namespace si {
    namespace model {
        /// The game scene, containing a player, bullets, shields, enemies...
        /// If this is in the `Game` entity, the game is in progress.
        class Scene : public Entity, public virtual Propagate<Entity>,
            public std::enable_shared_from_this<Scene> {
        public:
            Scene();
            void observeChildren();
            void update(const sf::Time &dt) override;
            void keyEvent(const controller::KeyEvent e);

            void setPlayerAcceleration(float x);
            void playerShoot();
        private:
            std::vector<std::shared_ptr<Invader>> invaders;
            std::vector<std::shared_ptr<Player>> players;
            std::vector<std::shared_ptr<PlayerBullet>> playerBullets;
        };
    }
}