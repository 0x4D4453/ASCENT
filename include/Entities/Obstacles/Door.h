#ifndef DOOR_H
#define DOOR_H

#include "Entities/Obstacles/Obstacle.h"
#include "Utility/Context.h"

namespace States { class StateStack; }
namespace Stages { class Stage; }

namespace Entities {
  namespace Obstacles {
    class Door : public Obstacle {
      private:
        States::StateStack* m_pStateStack;
        Context* m_pContext;
        Stages::Stage* m_pStage;
      
      public:
        Door(Textures::ID textureID, sf::Texture& texture, sf::Vector2f position = sf::Vector2f(0.f, 0.f), Stages::Stage* pStage = NULL);
        ~Door();
        void moveToNextStage();
        virtual void reactToCollision(Entity *pEntity, Manager::Collision::CollisionType type, float overlap);
        virtual void exec();
    };
  } 
}

#endif