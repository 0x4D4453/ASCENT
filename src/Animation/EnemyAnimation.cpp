/* Main Include */
#include "Animation/EnemyAnimation.h"

/* Program Defined */
#include "Entities/Enemy.h"
#include "Utility/Constants.h"

namespace Animations {
  EnemyAnimation::EnemyAnimation(Entities::Entity* pEntity, float timePerFrame) 
    : Animation(pEntity, timePerFrame)
  {
    m_currentFrame = static_cast<int>(Walk1);
  }

  EnemyAnimation::~EnemyAnimation() {

  }

  void EnemyAnimation::update(const float deltaTime, Entities::Enemy* pEnemy) {
    update(deltaTime, pEnemy, m_pEntity->getVelocity());
  }

  void EnemyAnimation::update(const float deltaTime, Entities::Enemy* pEnemy, const sf::Vector2f velocity) {
    if (pEnemy->getHealthPoints() <= 0)
      m_textureRect.left = Constants::SPRITE_SIZE * 4;
    else if (velocity.x == 0.f)
      m_textureRect.left = 0;
    else {
      m_totalTime += deltaTime;
      if (m_totalTime >= m_timePerFrame) {
        m_totalTime -= m_timePerFrame;
        m_textureRect.left = Constants::SPRITE_SIZE * m_currentFrame;
        ++m_currentFrame;
        if (m_currentFrame > static_cast<int>(DefaultFrames::Walk2))
          m_currentFrame = static_cast<int>(DefaultFrames::Walk1);
      }
    }
    m_pEntity->setTextureRect(m_textureRect);
  }
}