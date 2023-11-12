/* Main Include */
#include "Manager/Collision/PlatformCollision.h"

/* Program Defined */
#include "Entities/Player.h"

namespace Manager {
  namespace Collision {
    PlatformCollision::PlatformCollision()
      : CollisionStrategy()
    {

    }

    PlatformCollision::~PlatformCollision() {

    }

  void PlatformCollision::collide(Entities::Entity* onwEntity, Entities::Entity* otherEntity, CollisionType type, float overlap) {
    switch (otherEntity->getEntityId()) {
      case Entities::EntityID::PlayerE:
        playerCollide(dynamic_cast<Entities::Player*>(otherEntity), type);
        break;
      default:
        break;
    }

    if (type == CollisionType::Horizontal) {
      otherEntity->move(sf::Vector2f(overlap, 0));
    } else {
      otherEntity->move(sf::Vector2f(0, overlap));
      otherEntity->setVelocity(sf::Vector2f(0.f, 0.f));
    }
  }

  void PlatformCollision::playerCollide(Entities::Player* player, CollisionType type) {
    if (type == CollisionType::Horizontal && player->getIsJumping()) {
      player->setVelocity(sf::Vector2f(-player->getVelocity().x * .5f, -2.5f));
      player->setIsStaggered(true);
    }
  }
  }
}