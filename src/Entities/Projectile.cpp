/* Main Include */
#include "Entities/Projectile.h"

/* Program Defined */
#include "Utility/Constants.h"
#include "Utility/Textures.h"

#include <cmath>

namespace Entities {
  Projectile::Projectile(sf::Vector2f position, sf::Vector2f direction, const float speed) 
    : Entity(position, speed)
    , m_direction(direction)
  {
    setEntityId(EntityID::ProjectileE);
    setup();
  }

  Projectile::~Projectile() {
    
  }

  void Projectile::setup() {  
    m_sprite.setScale(sf::Vector2f(Constants::SCALE, Constants::SCALE));
  }

  void Projectile::exec() {
    move();
  }

  void Projectile::save() {

  }
}