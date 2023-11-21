#ifndef VIEWSHAKE_H
#define VIEWSHAKE_H

/* SFML Library */
#include <SFML/Graphics.hpp>

class ViewShake {
  private:
    sf::View* m_view;
    float m_elapsed;
    float m_totalTime;
    int m_direction;

  private:

  public:
    ViewShake(sf::View* view);
    ~ViewShake();
    void shake(const float dt, const int maxIntensity, const float interval);
    void reset();
    const bool finished(const float duration);
};

#endif