#ifndef VIEWSHAKE_H
#define VIEWSHAKE_H

/* SFML Library */
#include <SFML/Graphics.hpp>

class ViewShake {
  private:
    std::vector<sf::View>* m_views;
    float m_elapsed;
    float m_totalTime;
    int m_direction;

  private:

  public:
    ViewShake(std::vector<sf::View>* views);
    ~ViewShake();
    void shake(const float dt, const int maxIntensity, const float interval);
    void reset();
    const bool finished(const float duration);
};

#endif