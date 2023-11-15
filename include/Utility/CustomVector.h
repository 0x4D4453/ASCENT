#ifndef CUSTOMVECTOR_H
#define CUSTOMVECTOR_H

/* SFML Library */
#include <SFML/Graphics.hpp>

class CustomVector {
  private:
    sf::Vector2f m_vector;

  public:
    CustomVector(sf::Vector2f vector);
    ~CustomVector();
    const float scalarProduct(sf::Vector2f vector) const;
    const float getMagnitude() const;
};

#endif