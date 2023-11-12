/* Main Include */
#include "Manager/Collision/PlayerCollision.h"

/* Program Defined */
#include "Entities/Player.h"

namespace Manager {
  namespace Collision {
    PlayerCollision::PlayerCollision()
      : CollisionStrategy()
    {

    }

    PlayerCollision::~PlayerCollision() {

    }

    void PlayerCollision::collide(Entities::Entity *ownEntity, Entities::Entity *otherEntity, Manager::Collision::CollisionType type, float overlap) {
      if (ownEntity->getEntityId() != Entities::EntityID::PlayerE)
        return;

      Entities::Player* player = dynamic_cast<Entities::Player*>(ownEntity);
      
      if (type == Manager::Collision::CollisionType::Vertical && player->getPosition().y <= otherEntity->getPosition().y) {
        player->setIsJumping(false);
        player->setIsStaggered(false);
      }
    }
  }
}