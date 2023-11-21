/* Main Include */
#include "Being.h"

/* Program Defined */
#include "Manager/GraphicsManager.h"

/* Standard Library */
#include <iostream>

Manager::GraphicsManager* Being::m_pGraphicsManager(Manager::GraphicsManager::getInstance());
const float Being::m_dt(m_pGraphicsManager->getTimePerFrame()->asSeconds());
int Being::m_cont(0);

Being::Being(const float scale) 
  : m_id(m_cont++)
  , m_scale(scale)
  , m_sprite()
{
  m_sprite.setScale(sf::Vector2f(m_scale, m_scale));
}

Being::~Being() {

}

const int Being::getId() const {
  return m_id;
}

const HitboxSprite* Being::getSprite() const {
  return &m_sprite;
}

const sf::FloatRect Being::getGlobalHitbox() const {
  return m_sprite.getGlobalHitbox();
}

void Being::setColor(sf::Color color) {
  m_sprite.setColor(color);
}

void Being::setTextureID(Textures::ID textureID) {
  m_textureID = textureID;
}

void Being::setTexture(sf::Texture& texture) {
  m_sprite.setTexture(texture);
  refreshHitbox();
}

void Being::setTextureRect(const sf::IntRect& textureRect) {
  m_sprite.setTextureRect(textureRect);
}

void Being::refreshHitbox() {
  m_sprite.setHitbox({ 0.f, 0.f, m_sprite.getGlobalBounds().width / m_scale, m_sprite.getGlobalBounds().height / m_scale });
}

void Being::draw() {
  m_pGraphicsManager->drawBeing(this);
}