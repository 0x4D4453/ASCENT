/* Main Include */
#include "Animation/EnemyAnimation.h"

/* Program Defined */
#include "Entities/Characters/Enemy.h"
#include "Utility/Constants.h"

namespace Animations {
  EnemyAnimation::EnemyAnimation(Entities::Entity* pEntity, MDirection direction, float timePerFrame) 
    : Animation(pEntity, timePerFrame)
    , m_mDirection(direction)
  {
    m_currentFrame = static_cast<int>(Walk1);
  }

  EnemyAnimation::~EnemyAnimation() {

  }

  void EnemyAnimation::update(const float deltaTime) {
    Entities::Characters::Enemy* pEnemy = dynamic_cast<Entities::Characters::Enemy*>(m_pEntity);

    if (pEnemy->getHealthPoints() <= 0)
      m_textureRect.left = Constants::SPRITE_SIZE * static_cast<int>(DefaultFrames::Neutralized);
    else if ((m_mDirection == MDirection::X && m_pEntity->getVelocity().x == 0.f) ||
              (m_mDirection == MDirection::Y && m_pEntity->getVelocity().y == 0.f))
      m_textureRect.left = Constants::SPRITE_SIZE * static_cast<int>(DefaultFrames::Idle);
    else
      changeFrame(deltaTime, DefaultFrames::Walk1, DefaultFrames::Walk2);

    m_pEntity->setTextureRect(m_textureRect);
  }
}