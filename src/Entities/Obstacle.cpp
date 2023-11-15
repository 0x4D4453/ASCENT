/* Main Include */
#include "Entities/Obstacle.h"

namespace Entities {
  Obstacle::Obstacle(sf::Vector2f position, const bool harmful) 
    : Entity(position)
    , m_harmful(harmful)
  {
    setEntityId(EntityID::ObstacleE);
    setEntityTag(EntityTag::ObstacleTag);

    setCollisionStrategy(EntityTag::EnemyTag, Manager::Collision::StrategyId::Default);
    setCollisionStrategy(EntityTag::PlayerTag, Manager::Collision::StrategyId::Default);
  }

  Obstacle::~Obstacle() {
    
  }
}