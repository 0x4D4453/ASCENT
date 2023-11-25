#include "Entities/Obstacles/Spike.h"

#include <iostream>

namespace Entities {
  namespace Obstacles {
    Spike::Spike(Textures::ID textureID, sf::Texture& texture, sf::Vector2f position)
      : Obstacle(position, true)
      , m_attack(1)
    {
      setEntityId(EntityID::SpikesE);
      setTextureID(textureID);
      setTexture(texture);
      setCollisionStrategy(EntityTag::PlayerTag, Manager::Collision::StrategyId::KnockbackCollision);
    }

    Spike::~Spike() {

    }

    void Spike::damagePlayer(Characters::Player* pPlayer) {
      if (pPlayer->getIsImmune())
        return;

      pPlayer->setHealthPoints(pPlayer->getHealthPoints() - m_attack);
    }

    void Spike::reactToCollision(Entity *pEntity, Manager::Collision::CollisionType type, float overlap) {
      switch (pEntity->getEntityTag()) {
        case EntityTag::PlayerTag:
          damagePlayer(dynamic_cast<Characters::Player*>(pEntity));
          break;
        default:
          break;
      }
    }

    void Spike::exec() {
      
    }
  } 
}