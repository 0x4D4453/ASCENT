/* Main Include */
#include "Entities/Obstacles/Spring.h"

/* Program Defined */
#include "Utility/Constants.h"

namespace Entities {
  namespace Obstacles {
    Spring::Spring(Textures::ID textureID, sf::Texture& texture, sf::Vector2f position) 
      : Obstacle(position)
      , m_textureRect(sf::IntRect(0, 0, Constants::SPRITE_SIZE, Constants::SPRITE_SIZE))
      , m_strength(12.5f)
      , m_chargeTime(3.f)
      , m_launchTime(0.2f)
      , m_chargeTimeElapsed(0.f)
      , m_launchTimeElapsed(0.f)
      , m_animationTime(0.f)
      , m_isCharging(false)
      , m_isLaunching(false)
      , m_currentFrame(0)
    {
      setEntityType(EntityType::Dynamic);
      setEntityId(EntityID::SpringE);
      setTextureID(textureID);
      setTexture(texture);
      setTextureRect(m_textureRect);
      refreshHitbox();

      m_sprite.setOrigin(Constants::SPRITE_SIZE / 2.f, 0.f);
    }

    Spring::~Spring() {

    }

    void Spring::checkCharge() {
      if (m_isCharging) {
        m_chargeTimeElapsed += m_dt;
        m_animationTime += m_dt;
        
        if (m_animationTime >= m_chargeTime / SpringFrames::TotalFrames) {
          m_animationTime = 0.f;
          m_currentFrame--;
          if (m_currentFrame < SpringFrames::Contracted)
            m_currentFrame = SpringFrames::Contracted;

          m_textureRect.left = Constants::SPRITE_SIZE * m_currentFrame;
        }

        if (m_chargeTimeElapsed >= m_chargeTime) {
          m_chargeTimeElapsed = 0.f;
          m_isCharging = false;
        }
      }
    }

    void Spring::checkLaunch() {
      if (m_isLaunching) {
        m_launchTimeElapsed += m_dt;
        m_animationTime += m_dt;
        
        if (m_animationTime >= m_launchTime / SpringFrames::TotalFrames) {
          m_animationTime = 0.f;
          m_currentFrame++;
          if (m_currentFrame > SpringFrames::Extended)
            m_currentFrame = SpringFrames::Extended;

          m_textureRect.left = Constants::SPRITE_SIZE * m_currentFrame;
        }

        if (m_launchTimeElapsed >= m_launchTime) {
          m_launchTimeElapsed = 0.f;
          m_isLaunching = false;
          m_isCharging = true;
        }
      }
    }

    void Spring::launch(Entity* pEntity) {
      m_isLaunching = true;

      sf::Vector2f velocity = pEntity->getVelocity();
      float angle = getLaunchAngle(pEntity->getPosition());
      
      velocity.y = m_strength * sin(angle);
      velocity.x = m_strength * cos(angle);

      pEntity->setVelocity(velocity);
    }

    const float Spring::getLaunchAngle(sf::Vector2f position) {
      sf::Vector2f ownPosition = getPosition();
      position.y = ownPosition.y - Constants::SPRITE_SIZE * 2;
      sf::Vector2f vector = position - ownPosition;
      return atan2(vector.y, vector.x);
    }

    void Spring::reactToCollision(Entity *pEntity, Manager::Collision::CollisionType type, float overlap) {
      if (pEntity->getEntityType() == Entities::EntityType::Static || m_isCharging || m_isLaunching)
        return;

      if (type == Manager::Collision::CollisionType::Vertical)
        launch(pEntity);
    }

    const bool Spring::getIsCharging() const {
      return m_isCharging;
    }

    const bool Spring::getIsLaunching() const {
      return m_isLaunching;
    }

    void Spring::exec() {
      checkCharge();
      checkLaunch();
      setTextureRect(m_textureRect);
    }
  }
}