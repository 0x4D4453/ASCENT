/* Main Include */
#include "Utility/ViewShake.h"

ViewShake::ViewShake(sf::View* view)
  : m_view(view)
  , m_elapsed(0.f)
  , m_totalTime(0.f)
  , m_direction(1)
{

};

ViewShake::~ViewShake() {
  m_view = NULL;
}

void ViewShake::shake(const float dt, const int maxIntensity, const float interval) {
  m_totalTime += dt;
  m_elapsed += dt;

  if (m_elapsed >= interval) {
    float intensity = (rand() % maxIntensity) / 10.f;
    m_view->rotate(intensity * m_direction);

    m_elapsed = 0.f;
    m_direction *= -1;
  }
}

const bool ViewShake::finished(const float duration) {
  bool finished = m_totalTime >= duration;

  if (finished)
    m_view->setRotation(0.f);

  return finished;
}

void ViewShake::reset() {
  m_view->setRotation(0.f);
  m_totalTime = 0.f;
  m_elapsed = 0.f;
}
