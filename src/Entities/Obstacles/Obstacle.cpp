/* Main Include */
#include "Entities/Obstacles/Obstacle.h"

namespace Entities {
  namespace Obstacles {
    Obstacle::Obstacle(sf::Vector2f position, const bool harmful) 
      : Entity(position)
      , m_harmful(harmful)
    {
      setEntityId(EntityID::ObstacleE);
      setEntityTag(EntityTag::ObstacleTag);

      setCollisionStrategy(EntityTag::EnemyTag, Manager::Collision::StrategyId::Default);
      setCollisionStrategy(EntityTag::PlayerTag, Manager::Collision::StrategyId::Default);
      setCollisionStrategy(EntityTag::ProjectileTag, Manager::Collision::StrategyId::BounceCollision);
    }

    Obstacle::~Obstacle() {
      
    }

    void Obstacle::save(nlohmann::ordered_json& jsonData) {
      Entity::save(jsonData);
    }

    void Obstacle::loadSave(const nlohmann::ordered_json& jsonData) {
      Entity::loadSave(jsonData);
    }
  }
}