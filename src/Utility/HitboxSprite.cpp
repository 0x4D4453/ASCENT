/* Main Include */
#include "Utility/HitboxSprite.h"

HitboxSprite::HitboxSprite()
  : m_hitbox({ 0.f, 0.f, 16.f, 16.f })
{

};

HitboxSprite::~HitboxSprite() {

}

sf::FloatRect HitboxSprite::getGlobalHitbox() const {
  return getTransform().transformRect(m_hitbox);
}

void HitboxSprite::setHitbox(const sf::FloatRect& hitbox) {
  m_hitbox = hitbox;
}