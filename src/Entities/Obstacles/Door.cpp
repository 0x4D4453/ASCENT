/* Main Include */
#include "Entities/Obstacles/Door.h"

/* Program Defined */
#include "State/State.h"
#include "State/StateStack.h"
#include "Stage/Stage.h"

namespace Entities {
  namespace Obstacles {
    Door::Door(Textures::ID textureID, sf::Texture& texture, sf::Vector2f position, Stages::Stage* pStage)
      : Obstacle(position, false)
      , m_pStateStack(States::StateStack::getInstance())
      , m_pContext(Context::getInstance())
      , m_pStage(pStage)
    {
      setEntityId(EntityID::DoorE);
      setTextureID(textureID);
      setTexture(texture);
    }

    Door::~Door() {

    }

    void Door::moveToNextStage() {
      Stages::ID stageID = static_cast<Stages::ID>(static_cast<int>(m_pContext->getStage()) + 1);

      if (stageID >= Stages::TotalStages) {
        m_pStateStack->pushState(States::StateType::EndStage, NULL);
        m_pStage->setPaused(true);
      } else {
        m_pContext->setStage(stageID);
        m_pStateStack->pushState(States::StateType::Loading, NULL, true);
      }
        
    }

    void Door::reactToCollision(Entity *pEntity, Manager::Collision::CollisionType type, float overlap) {
      switch (pEntity->getEntityTag()) {
        case EntityTag::PlayerTag:
          moveToNextStage();
          break;
        default:
          break;
      }
    }

    void Door::exec() {

    }
  }
}