#include "Entities/Obstacles/Spike.h"

#include <iostream>

namespace Entities {
  namespace Obstacles {
    Spike::Spike(sf::Texture& texture, sf::Vector2f position)
      : Obstacle(position, true)
      , m_attack(1)
    {
      setTexture(texture);
      setCollisionStrategy(EntityTag::PlayerTag, Manager::Collision::StrategyId::KnockbackCollision);
    }

    Spike::~Spike() {

    }


    void Spike::damagePlayer(Characters::Player* pPlayer) {
      pPlayer->setHealthPoints(pPlayer->getHealthPoints() - m_attack);
      std::cout << pPlayer->getHealthPoints() << std::endl;
    }

    void Spike::collide(Entity *pEntity, Manager::Collision::CollisionType type, float overlap) {
      Characters::Player* player = dynamic_cast<Characters::Player*>(pEntity);
      damagePlayer(player);
    }

    
    void Spike::save() {

    }

    void Spike::exec() {
      
    }

  } 
}