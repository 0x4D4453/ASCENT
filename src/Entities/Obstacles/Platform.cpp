/* Main Include */
#include "Entities/Obstacles/Platform.h"

/* Program Defined */
#include "Utility/Constants.h"

/* Forward Declaration */
#include "Entities/Characters/Player.h"

namespace Entities {
  namespace Obstacles {
    Platform::Platform(Textures::ID textureID, sf::Texture& texture, sf::Vector2f position) 
      : Obstacle(position)
    {
      setEntityId(EntityID::PlatformE);
      setTextureID(textureID);
      setTexture(texture);
    }

    Platform::~Platform() {

    }

    void Platform::setup(const char* file) {
      
    }

    void Platform::reactToCollision(Entity *pEntity, Manager::Collision::CollisionType type, float overlap) {
      switch (pEntity->getEntityId()) {
        case EntityID::FlyE:
          return;
        case EntityID::PlayerE:
          playerCollide(dynamic_cast<Characters::Player*>(pEntity), type);
          break;
        default:
          break;
      }
    }

    void Platform::playerCollide(Characters::Player* pPlayer, Manager::Collision::CollisionType type) {
      if (type == Manager::Collision::CollisionType::Horizontal && pPlayer->getIsMidAir()) {
        pPlayer->setVelocity(sf::Vector2f(-pPlayer->getVelocity().x * .5f, pPlayer->getVelocity().y));
        pPlayer->setIsStaggered(true);
      }
    }

    void Platform::exec() {
      
    }
  }
}