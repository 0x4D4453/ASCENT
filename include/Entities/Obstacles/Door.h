#ifndef DOOR_H
#define DOOR_H

#include "Entities/Obstacles/Obstacle.h"
#include "Utility/Context.h"

namespace States { class StateStack; }

namespace Entities {
  namespace Obstacles {
    class Door : public Obstacle {
      private:
        States::StateStack* m_pStateStack;
        Context* m_pContext;
      
      public:
        Door(Textures::ID textureID, sf::Texture& texture, sf::Vector2f position = sf::Vector2f(0.f, 0.f));
        ~Door();
        void moveToNextStage();
        virtual void reactToCollision(Entity *pEntity, Manager::Collision::CollisionType type, float overlap);
        virtual void save(nlohmann::ordered_json& jsonData);
        virtual void loadSave(const nlohmann::ordered_json& jsonData);
        virtual void exec();
    };
  } 
}

#endif