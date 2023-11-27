/* Main Include */
#include "UI/PlayerHealth.h"

/* Program Defined */
#include "Entities/Characters/Player.h"
#include "Manager/GraphicsManager.h"
#include "Utility/Constants.h"
#include "Utility/Textures.h"

/* Standard Library */
#include <iostream>

namespace UI {
  PlayerHealth::PlayerHealth()
    : m_maxHearts(10)
    , m_heartTexture()
    , m_heartContainer()
    , m_textureRect(sf::IntRect(0, 0, Constants::SPRITE_SIZE, Constants::SPRITE_SIZE))
    , m_timePerFrame(0.5f)
    , m_totalTime(0.f)
    , m_currentFrame(0)
  {
    if (!m_heartTexture.loadFromFile(Textures::HEART))
      std::cerr << "Error loading heart font" << std::endl;

    for (int i = 0; i < m_maxHearts; ++i) {
      sf::Sprite heartSprite(m_heartTexture);
      heartSprite.setScale(Constants::SCALE, Constants::SCALE);
      heartSprite.setColor(sf::Color::Red);
      m_heartContainer.push_back(heartSprite);
    }
  }

  PlayerHealth::~PlayerHealth() {

  }

  void PlayerHealth::update(const float dt) {
    m_totalTime += dt;
    if (m_totalTime >= m_timePerFrame) {
      m_totalTime = 0.f;
      m_textureRect.left = Constants::SPRITE_SIZE * m_currentFrame;
      ++m_currentFrame;
      if (m_currentFrame > 2)
        m_currentFrame = 0;
    }
  }

  void PlayerHealth::draw(Entities::Characters::Player* pPlayer, Manager::GraphicsManager* pGraphicsManager) {
    sf::Vector2f viewPosition = pGraphicsManager->getViewCoordinates();

    for (int i = 0; i < pPlayer->getHealthPoints(); ++i) {
      m_heartContainer[i].setTextureRect(m_textureRect);
      m_heartContainer[i].setPosition(sf::Vector2f(viewPosition.x + 10.f + (30.f * i), viewPosition.y + 10.f));
      pGraphicsManager->draw(m_heartContainer[i]);
    }  
  }
}