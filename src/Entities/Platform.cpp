/* Main Include */
#include "Entities/Platform.h"

/* Program Defined */
#include "Utility/Constants.h"

/* Forward Declaration */
#include "Entities/Player.h"

namespace Entities {
  Platform::Platform(sf::Texture& texture, sf::Vector2f position) 
    : Obstacle(position)
  {
    setEntityId(EntityID::PlatformE);
    setTexture(texture);

    m_pCollision = m_pCollisionFactory->getCollisionStrategy(Manager::Collision::StrategyId::Platform);
  }

  Platform::~Platform() {

  }

  void Platform::setup(const char* file) {
    
  }

  void Platform::save() {

  }

  void Platform::exec() {
    
  }
}