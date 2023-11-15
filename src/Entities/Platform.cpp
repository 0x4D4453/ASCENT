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

  void Platform::collide(Entity *entity, Manager::Collision::CollisionType type, float overlap) {
    switch (entity->getEntityId()) {
      case EntityID::FlyE:
        return;
      case EntityID::PlayerE:
        playerCollide(dynamic_cast<Player*>(entity), type);
        break;
      default:
        break;
    }
  }

  void Platform::playerCollide(Player* player, Manager::Collision::CollisionType type) {
    if (type == Manager::Collision::CollisionType::Horizontal && player->getIsJumping()) {
      player->setVelocity(sf::Vector2f(-player->getVelocity().x * .5f, player->getVelocity().y));
      player->setIsStaggered(true);
    }
  }

  void Platform::save() {

  }

  void Platform::exec() {
    
  }
}