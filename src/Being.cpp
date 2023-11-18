/* Main Include */
#include "Being.h"

/* Program Defined */
#include "Manager/GraphicsManager.h"
#include "Utility/Constants.h"

/* Standard Library */
#include <iostream>

Manager::GraphicsManager* Being::m_pGraphicsManager(Manager::GraphicsManager::getInstance());
const float Being::m_dt(m_pGraphicsManager->getTimePerFrame()->asSeconds());
int Being::m_cont(0);

Being::Being() 
  : m_id(m_cont++)
{
  m_sprite.setScale(sf::Vector2f(Constants::SCALE, Constants::SCALE));
}

Being::~Being() {

}

const int Being::getId() const {
  return m_id;
}

const sf::Sprite* Being::getSprite() const {
  return &m_sprite;
}

const sf::FloatRect Being::getGlobalBounds() const {
  return m_sprite.getGlobalBounds();
}

void Being::setTextureID(Textures::ID textureID) {
  m_textureID = textureID;
}

void Being::setTexture(sf::Texture& texture) {
  m_sprite.setTexture(texture);
}

void Being::setTextureRect(const sf::IntRect& textureRect) {
  m_sprite.setTextureRect(textureRect);
}

void Being::draw() {
  m_pGraphicsManager->drawBeing(this);
}