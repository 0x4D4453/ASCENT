/* Main Include */
#include "Being.h"

/* Program Defined */
#include "Manager/GraphicsManager.h"

/* Standard Library */
#include <iostream>

Manager::GraphicsManager* Being::m_pGraphicsManager(Manager::GraphicsManager::getInstance());

Being::Being() 
  : m_id(0)
{

}

Being::~Being() {

}

const sf::Sprite* Being::getSprite() const {
  return &m_sprite;
}

const sf::FloatRect Being::getGlobalBounds() const {
  return m_sprite.getGlobalBounds();
}

void Being::setTexture(const char* file) {
  if (!m_texture.loadFromFile(file)) 
    std::cerr << "Error loading texture " << file << "\n";
  m_sprite.setTexture(m_texture);
}

void Being::draw() {
  m_pGraphicsManager->drawBeing(this);
}