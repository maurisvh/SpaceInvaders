#pragma once
#include "key-event.h"
#include "entity.h"
#include "scene.h"
#include "observer.h"
#include "title-screen.h"
#include "optional.h"

#include <deque>

namespace si {
    namespace model {
        class Game : public Entity,
            public virtual Observer<Message>,
            public virtual Observer<controller::KeyAction> {
        public:
            Game();
			void observeChildren();
            void update(const sf::Time &dt) override;
            void onEvent(const Message& m) override;
	        void onEvent(const controller::KeyAction&) override;
	        void nextLevel();
			bool quitting() const;
			bool playing() const;

        private:
	        optional<TitleScreen> titleScreen;
            optional<Scene> scene;
	        std::deque<std::vector<std::shared_ptr<Entity>>> levelBuffer;
			bool m_quitting;
	        int levelNumber;
        };
    }
}
