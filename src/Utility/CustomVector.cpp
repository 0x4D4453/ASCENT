/* Main Include */
#include "Utility/CustomVector.h"

/* Standard Library */
#include <math.h>

CustomVector::CustomVector(sf::Vector2f vector)
  : m_vector(vector)
{

};

CustomVector::~CustomVector() {

}

const float CustomVector::scalarProduct(sf::Vector2f vector) const {
  // Vector scalar product (GAAL)
  return m_vector.x * vector.x + m_vector.y * vector.y;
}

const float CustomVector::getMagnitude() const {
  // Vector magnitude (GAAL)
  return sqrt(abs(scalarProduct(m_vector)));
}