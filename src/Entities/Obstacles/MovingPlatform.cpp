/* Main Include */
#include "Entities/Obstacles/MovingPlatform.h"
#include "Entities/Characters/Player.h"

/* Program Defined */
#include "Utility/Constants.h"

namespace Entities {
  namespace Obstacles {
    MovingPlatform::MovingPlatform(sf::Texture& texture, sf::Vector2f position)
      : Obstacle(position)
      , m_spawnPosition(position)
      , m_range(64.f)
      , m_direction(true)
    {
      setEntityId(EntityID::MovingPlatformE);
      setEntityType(EntityType::Dynamic);
      setTexture(texture);
      setSpeed(50.f);
    }

    MovingPlatform::~MovingPlatform() {

    }

    void MovingPlatform::movementPattern() {
      sf::Vector2f velocity = sf::Vector2f(m_speed * m_dt, 0.f);

      if (getPosition().x >= (m_spawnPosition.x + m_range))
        m_direction = true;
      else if (getPosition().x <= (m_spawnPosition.x - m_range))
        m_direction = false;
      
      if (m_direction)
        velocity.x = -m_speed * m_dt;
      else
        velocity.x = m_speed * m_dt;

      m_velocity = velocity;
      move();
    }

    void MovingPlatform::collide(Entity *pEntity, Manager::Collision::CollisionType type, float overlap) {
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

    void MovingPlatform::playerCollide(Characters::Player* pPlayer, Manager::Collision::CollisionType type) {
      if (type == Manager::Collision::CollisionType::Horizontal && pPlayer->getIsMidAir()) {
        pPlayer->setVelocity(sf::Vector2f(-pPlayer->getVelocity().x * .5f, pPlayer->getVelocity().y));
        pPlayer->setIsStaggered(true);
      }
    }

    void MovingPlatform::save() {

    }

    void MovingPlatform::exec() {
      movementPattern();
    }
  }
}