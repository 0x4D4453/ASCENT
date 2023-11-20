#ifndef TYRANT_H
#define TYRANT_H

/* Program Defined */
#include "Entities/Characters/Enemy.h"
#include "Entities/EntityList.h"
#include "Entities/Characters/TyrantStates/TyrantState.h"
#include "Animation/TyrantAnimation.h"
#include "Utility/Textures.h"

/* JSON Library */
#include "nlohmann/json.hpp"

namespace Entities {
  namespace Characters {
    class Tyrant : public Enemy {
      private:
        const float m_followDistance;
        Animations::TyrantAnimation m_animation;
        TyrantState* m_pState;
        EntityList* m_pPlayers;
        float m_timeSinceAction;

      private:
        virtual void update();
        // void jump();
        // void chargeJump();
        // void launchProjectiles();
        // void followPlayer(sf::Vector2f playerPosition);

      public:
        Tyrant(Textures::ID textureID, sf::Texture& texture, const sf::Vector2f spawnPosition = sf::Vector2f(0.f, 0.f), EntityList* pPlayers = NULL);
        ~Tyrant();
        void changeState(TyrantStateID id);
        virtual void movementPattern();
        virtual void save(nlohmann::ordered_json& jsonData);
        virtual void loadSave(const nlohmann::ordered_json& jsonData);
    };
  }
}

#endif