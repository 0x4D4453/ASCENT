/* Main Include */
#include "Entities/Platform.h"

/* Program Defined */
#include "Utility/Constants.h"

namespace Entities {
  Platform::Platform(sf::Texture& texture, sf::Vector2f position) 
    : Obstacle(position)
  {
    setTexture(texture);
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