/* Main Include */
#include "Entities/Platform.h"

/* Program Defined */
#include "Utility/Constants.h"

namespace Entities {
  Platform::Platform(sf::Vector2f position, const char* file) 
    : Obstacle(position)
  {
    setup(file);
  }

  Platform::~Platform() {

  }

  void Platform::setup(const char* file) {
    setTexture(file);
  }

  void Platform::save() {

  }

  void Platform::exec() {
    
  }
}