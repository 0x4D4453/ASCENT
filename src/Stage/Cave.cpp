/* Main Include */
#include "Stage/Cave.h"

/* Program Defined */
#include "State/GameState.h"

namespace Stages {
  Cave::Cave(States::GameState* pGameState, const std::string& mapTxt) 
    : Stage(pGameState, mapTxt)
    , m_pFly(NULL)
    , m_pGoomba(NULL)
    , m_maxFlyInstances(4)
    , m_maxGoombaInstances(2)
    , m_flyChance(50)
    , m_goombaChance(33)
    , m_flyNumber(0)
    , m_goombaNumber(0)
  {

  }

  Cave::~Cave() {
    m_pFly = NULL;
    m_pGoomba = NULL;
  }

  void Cave::createFly(sf::Vector2f& position) {
    if (m_flyNumber >= m_maxFlyInstances)
      return;

    const int random = 1 + rand() % 100;
    if (random < m_flyChance) {
      sf::Texture& textureRef = m_pEntityFactory->getTexture(Textures::Fly);
      m_pFly = new Entities::Characters::Fly(Textures::Fly, textureRef, position);
      m_dynamicEntities.include(static_cast<Entities::Entity*>(m_pFly));
    }
  }

  void Cave::createGoomba(sf::Vector2f& position) {
    if (m_goombaNumber >= m_maxGoombaInstances)
      return;

    const int random = 1 + rand() % 100;
    if (random < m_goombaChance) {
      sf::Texture& textureRef = m_pEntityFactory->getTexture(Textures::Goomba);
      m_pGoomba = new Entities::Characters::Goomba(Textures::Goomba, textureRef, position);
      m_dynamicEntities.include(static_cast<Entities::Entity*>(m_pGoomba));
    }
  }

  void Cave::createRandomEnemy(sf::Vector2f& position) {
    if (rand() % 2)
      createFly(position);
    else
      createGoomba(position);
  }
}
