#pragma once
#include "entity.h"
#include <vector>
#include "invader.h"
#include "player.h"
#include "bullet.h"
#include "key-event.h"
#include "shield.h"
#include "popup.h"
#include "optional.h"

namespace si {
    namespace model {
        /// The game scene, containing a player, bullets, shields, enemies...
        /// If this is in the `Game` entity, the game is in progress.
        class Scene : public Entity,
            public virtual Observer<Message> {
        public:
			enum class State {
				IntroCard,	   // The "Level ..." card is being displayed.
				Playing,	   // The game is in progress.
				VictoryCard,   // The "Victory" card is being displayed.
				Victory,	   // The game has finished; the player won.
				GameOverCard,  // The "Game Over" card is being displayed.
				GameOver,	   // The game has finished; the player lost.
			};
			
			Scene();
	        explicit Scene(std::vector<std::shared_ptr<Entity>> entities,
						   optional<int> levelNumber);
			
            void observeChildren();
            void onEvent(const Message& m) override;

	        void update(const sf::Time &dt) override;
            void keyAction(const controller::KeyAction e);

            void setPlayerAcceleration(float x);
            void playerShoot();

			State state() const;
	        bool finished() const;

        private:
            template <typename E>
            void playerBulletsCollideWith(std::vector<std::shared_ptr<E>> &entities);

            template <typename E>
            void enemyBulletsCollideWith(std::vector<std::shared_ptr<E>> &entities);
			void Scene::invaderCollisions();

            void collectPlayerBullets();
            void collectEnemyBullets();
			void simulate(const sf::Time &dt);

			void showPopup(const std::string str, sf::Time duration = sf::seconds(2.0f));

			std::vector<std::shared_ptr<Invader>> invaders;
            std::vector<std::shared_ptr<Player>> players;
            std::vector<std::shared_ptr<Shield>> shields;
            std::vector<std::shared_ptr<PlayerBullet>> playerBullets;
			std::vector<std::shared_ptr<EnemyBullet>> enemyBullets;
			std::vector<std::shared_ptr<Popup>> popups;
	        
			State m_state;
        };
    }
}
