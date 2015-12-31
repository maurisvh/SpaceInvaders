#pragma once
#include "entity.h"
#include "message.h"

namespace si {
    namespace model {
        class Shield : public PhysicalEntity,
            public virtual IPlayerBulletTarget,
            public virtual IEnemyBulletTarget {
        public:
            static const float size;
            Shield(sf::Vector2f p, int h);
			
            int health() const;
            void update(const sf::Time& dt) override;
            void shot();
            void shotByPlayer() override;
            void shotByEnemy() override;

        private:
            int m_health;
        };
    }
}


