/* Main Include */
#include "Utility/HitboxSprite.h"

HitboxSprite::HitboxSprite()
  : Sprite()
  , m_hitbox()
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