/* Main Include */
#include "Entities/Platform.h"

/* Program Defined */
#include "Utility/Constants.h"

/* Forward Declaration */
#include "Entities/Player.h"

namespace Entities {
  Platform::Platform(sf::Texture& texture, sf::Vector2f position) 
    : Obstacle(position)
  {
    setEntityId(EntityID::PlatformE);
    setTexture(texture);
  }

  Platform::~Platform() {

  }

  void Platform::setup(const char* file) {
    
  }

  void Platform::collide(Entity* entity, CollisionType type, float overlap) {
    switch (entity->getEntityId()) {
      case PlayerE:
        playerCollide(dynamic_cast<Player*>(entity), type);
        break;
      default:
        break;
    }

    if (type == CollisionType::Horizontal) {
      entity->move(sf::Vector2f(overlap, 0));
    } else {
      entity->move(sf::Vector2f(0, overlap));
      entity->setVelocity(sf::Vector2f(0.f, 0.f));
    }
  }

  void Platform::playerCollide(Player* player, CollisionType type) {
    if (type == CollisionType::Horizontal && player->getIsJumping()) {
      player->setVelocity(sf::Vector2f(-player->getVelocity().x * .5f, -2.5f));
      player->setIsStaggered(true);
    }
  }

  void Platform::save() {

  }

  void Platform::exec() {
    
  }
}