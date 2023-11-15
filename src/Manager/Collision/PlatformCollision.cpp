/* Main Include */
#include "Manager/Collision/PlatformCollision.h"

/* Program Defined */
#include "Entities/Player.h"

namespace Manager {
  namespace Collision {
    PlatformCollision::PlatformCollision()
      : CollisionStrategy()
    {
      m_defaultCollision = m_pCollisionStrategyFactory->getCollisionStrategy(StrategyId::Default);
    }

    PlatformCollision::~PlatformCollision() {
      m_defaultCollision = NULL;
    }

    void PlatformCollision::collide(Entities::Entity* onwEntity, Entities::Entity* otherEntity, CollisionType type, float overlap) {
      if (otherEntity->getEntityId() != Entities::EntityID::PlayerE)
        return;
        
      playerCollide(onwEntity, dynamic_cast<Entities::Player*>(otherEntity), type);
      m_defaultCollision->collide(onwEntity, otherEntity, type, overlap);
    }

    void PlatformCollision::playerCollide(Entities::Entity *ownEntity, Entities::Player* player, CollisionType type) {
      if (type == CollisionType::Horizontal && player->getIsJumping()) {
        player->setVelocity(sf::Vector2f(-player->getVelocity().x * .5f, player->getVelocity().y));
        player->setIsStaggered(true);
      }
    }
  }
}