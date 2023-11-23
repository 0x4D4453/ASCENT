/* Main Include */
#include "Stage/Cave.h"

/* Program Defined */
#include "State/GameState.h"

namespace Stages {
  Cave::Cave(ResourceHolder<Textures::ID, sf::Texture>* pTextureHolder, Entities::EntityFactory* pEntityFactory, States::GameState* pGameState) 
    : Stage(pTextureHolder, pEntityFactory, pGameState, Constants::CAVE)
    , m_pFly(NULL)
    , m_maxFlyInstances(4)
    , m_flyChance(50)
    , m_flyNumber(0)
  {
    m_bgMusic.openFromFile(Sounds::CAVE_BG);
    m_bgMusic.setVolume(10);
    m_bgMusic.setLoop(true);
    m_bgMusic.play();
  }

  Cave::~Cave() {
    m_pFly = NULL;
    m_bgMusic.stop();
  }

  void Cave::loadTextures() {
    if (!m_pTextureHolder) {
      std::cerr << "Error loading textures" << std::endl;
      exit(1);
    }

    m_pTextureHolder->load(Textures::StagePlatform, Textures::STONE_PLATFORM_MIDDLE);
    m_pTextureHolder->load(Textures::StagePlatformLeft, Textures::STONE_PLATFORM_LEFT);
    m_pTextureHolder->load(Textures::StagePlatformRight, Textures::STONE_PLATFORM_RIGHT);
    m_pTextureHolder->load(Textures::StageWallLeft, Textures::STONE_WALL_LEFT);
    m_pTextureHolder->load(Textures::StageWallMiddle, Textures::STONE_WALL_MIDDLE);
    m_pTextureHolder->load(Textures::StageWallRight, Textures::STONE_WALL_RIGHT);
    m_pTextureHolder->load(Textures::StageCeiling, Textures::STONE_CEILING_MIDDLE);
    m_pTextureHolder->load(Textures::StageCeilingLeft, Textures::STONE_CEILING_LEFT);
    m_pTextureHolder->load(Textures::StageCeilingRight, Textures::STONE_CEILING_RIGHT);
    m_pTextureHolder->load(Textures::StagePilar, Textures::STONE_PILAR_MIDDLE);
    m_pTextureHolder->load(Textures::StagePilarTop, Textures::STONE_PILAR_TOP);
    m_pTextureHolder->load(Textures::StagePilarBottom, Textures::STONE_PILAR_BOTTOM);

    m_pTextureHolder->load(Textures::Bridge, Textures::BRIDGE_MIDDLE);
    m_pTextureHolder->load(Textures::BridgeLeft, Textures::BRIDGE_LEFT);
    m_pTextureHolder->load(Textures::BridgeRight, Textures::BRIDGE_RIGHT);

    m_pTextureHolder->load(Textures::Spikes, Textures::STALACTITE);
    m_pTextureHolder->load(Textures::Door, Textures::DOOR);
    m_pTextureHolder->load(Textures::Fly, Textures::FLY);
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

  void Cave::createRandomEnemy(sf::Vector2f& position) {
    if (rand() % 2)
      createFly(position);
    else
      createGoomba(position);
  }

  void Cave::createRandomObstacle(sf::Vector2f& position) {
    createSpike(position);
  }
}
