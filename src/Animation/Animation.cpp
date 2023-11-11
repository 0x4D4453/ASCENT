/* Main Include */
#include "Animation/Animation.h"

/* Program Defined */
#include "Entities/Entity.h"

namespace Animations {
  Animation::Animation(Entities::Entity* pEntity, float timePerFrame) 
    : m_pEntity(pEntity)
    , m_animationFrames()
    , m_totalTime(0.f)
    , m_timePerFrame(timePerFrame)
  {

  }

  Animation::~Animation() {

  }

  void Animation::includeFrame(sf::Texture* pFrame) {
    if (pFrame)
      m_animationFrames.push_back(pFrame);
  }
}