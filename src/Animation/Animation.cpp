/* Main Include */
#include "Animation/Animation.h"

/* Program Defined */
#include "Entities/Entity.h"
#include "Utility/Constants.h"

namespace Animations {
  Animation::Animation(Entities::Entity* pEntity, float timePerFrame) 
    : m_pEntity(pEntity)
    , m_textureRect(sf::IntRect(0, 0, Constants::SPRITE_SIZE, Constants::SPRITE_SIZE))
    , m_totalTime(0.f)
    , m_timePerFrame(timePerFrame)
  {
    m_pEntity->setTextureRect(m_textureRect);
    m_pEntity->refreshHitbox();
  }

  Animation::~Animation() {

  }

  void Animation::changeFrame(const float deltaTime, const int firstFrame, const int lastFrame) {
    m_totalTime += deltaTime;
    if (m_totalTime >= m_timePerFrame) {
      m_currentFrame++;
      if (m_currentFrame < firstFrame || m_currentFrame > lastFrame)
        m_currentFrame = firstFrame;

      m_totalTime -= m_timePerFrame;
      m_textureRect.left = Constants::SPRITE_SIZE * m_currentFrame;
    }
  }

  const int Animation::getCurrentFrame() const {
    return m_currentFrame;
  }

  void Animation::setTimePerFrame(const float timePerFrame) {
    m_timePerFrame = timePerFrame;
  }
}