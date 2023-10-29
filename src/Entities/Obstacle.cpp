/* Main Include */
#include "Entities/Obstacle.h"

namespace Entities {
  Obstacle::Obstacle(sf::Vector2f position, const bool harmful) 
    : Entity(position)
    , m_harmful(harmful)
  {

  }

  Obstacle::~Obstacle() {
    
  }
}