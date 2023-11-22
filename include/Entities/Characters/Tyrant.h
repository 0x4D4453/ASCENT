#ifndef TYRANT_H
#define TYRANT_H

/* Program Defined */
#include "Entities/Characters/Enemy.h"
#include "Entities/Characters/TyrantStates/TyrantState.h"
#include "Utility/Textures.h"

/* JSON Library */
#include "nlohmann/json.hpp"

/* Forward Declaration */
namespace Stages { class Stage; }

namespace Entities {
  namespace Characters {
    class Tyrant : public Enemy {
      private:
        Stages::Stage* m_pStage;
        TyrantState* m_pState;
        float m_maxSpeed;

      private:
        virtual void update();
        virtual void playerCollide(Characters::Player* pPlayer, Manager::Collision::CollisionType type);

      public:
        Tyrant(Textures::ID textureID, sf::Texture& texture, const sf::Vector2f spawnPosition = sf::Vector2f(0.f, 0.f), Stages::Stage* pStage = NULL);
        ~Tyrant();

        TyrantState* getState() const;
        void changeState(TyrantStateID id);
        Animations::Animation* getAnimation();
        const float getMaxSpeed() const;
        void changeMaxSpeed(const float maxSpeed);

        virtual void movementPattern();
        virtual void collide(Entity *pEntity, Manager::Collision::CollisionType type, float overlap);
        virtual void save(nlohmann::ordered_json& jsonData);
        virtual void loadSave(const nlohmann::ordered_json& jsonData);
    };
  }
}

#endif