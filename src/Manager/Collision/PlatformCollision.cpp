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
      case Entities::EntityID::FlyE:
        return;
      case Entities::EntityID::PlayerE:
        playerCollide(onwEntity, dynamic_cast<Entities::Player*>(otherEntity), type);
        break;
      default:
        if (type == CollisionType::Vertical)
          otherEntity->setVelocity(sf::Vector2f(otherEntity->getVelocity().x, 0.f));
        break;
    }

    if (type == CollisionType::Horizontal)
      otherEntity->move(sf::Vector2f(overlap, 0));
    else
      otherEntity->move(sf::Vector2f(0, overlap));
  }

  void PlatformCollision::playerCollide(Entities::Entity *ownEntity, Entities::Player* player, CollisionType type) {
    if (type == CollisionType::Horizontal && player->getIsJumping()) {
      player->setVelocity(sf::Vector2f(-player->getVelocity().x * .5f, player->getVelocity().y));
      player->setIsStaggered(true);
    } else {
      if (ownEntity->getPosition().y >= player->getPosition().y)
        player->setVelocity(sf::Vector2f(0.f, 0.f));
      else
        player->setVelocity(sf::Vector2f(player->getVelocity().x * .5f, 0.f));
    }
  }
  }
}