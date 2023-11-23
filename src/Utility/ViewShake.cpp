/* Main Include */
#include "Utility/ViewShake.h"

ViewShake::ViewShake(std::vector<sf::View>* views)
  : m_views(views)
  , m_elapsed(0.f)
  , m_totalTime(0.f)
  , m_direction(1)
{

};

ViewShake::~ViewShake() {
  m_views = NULL;
}

void ViewShake::shake(const float dt, const int maxIntensity, const float interval) {
  m_totalTime += dt;
  m_elapsed += dt;

  if (m_elapsed >= interval) {
    float intensity = (rand() % maxIntensity) / 10.f;
    std::vector<sf::View>::iterator it;

    for (it = m_views->begin(); it != m_views->end(); it++)
      (*it).rotate(intensity * m_direction);

    m_elapsed = 0.f;
    m_direction *= -1;
  }
}

const bool ViewShake::finished(const float duration) {
  bool finished = m_totalTime >= duration;

  if (finished) {
    std::vector<sf::View>::iterator it;
    for (it = m_views->begin(); it != m_views->end(); it++)
      (*it).setRotation(0.f);
  }

  return finished;
}

void ViewShake::reset() {
  std::vector<sf::View>::iterator it;
  for (it = m_views->begin(); it != m_views->end(); it++)
    (*it).setRotation(0.f);
    
  m_totalTime = 0.f;
  m_elapsed = 0.f;
}
