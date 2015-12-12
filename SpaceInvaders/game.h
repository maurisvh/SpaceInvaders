#pragma once
#include "key-event.h"
#include "entity.h"
#include "scene.h"
#include "observer.h"

namespace si {
    namespace model {
        class Game : public Entity,
            public virtual Propagate<Message>,
            public virtual Observer<controller::KeyEvent>,
            public std::enable_shared_from_this<Game> {
        public:
            Game();
            void observeChildren();
            void update(const sf::Time &dt) override;
            void onEvent(const controller::KeyEvent&) override;

        private:
            std::vector<std::shared_ptr<Scene>> scenes;
        };
    }
}