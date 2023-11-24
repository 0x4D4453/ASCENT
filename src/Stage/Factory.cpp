/* Main Include */
#include "Stage/Factory.h"

/* Program Defined */
#include "State/GameState.h"


namespace Stages {
  Factory::Factory(ResourceHolder<Textures::ID, sf::Texture>* pTextureHolder, Entities::EntityFactory* pEntityFactory, States::GameState* pGameState) 
    : Stage(pTextureHolder, pEntityFactory, pGameState, Constants::FACTORY)
    , m_pTyrant(NULL)
    , m_maxTyrantInstances(2)
    , m_tyrantChance(20)
    , m_tyrantNumber(0)
    , m_pSpring(NULL)
    , m_maxSpringInstances(4)
    , m_springChance(40)
    , m_springNumber(0)
  {
    m_bgMusic.openFromFile(Sounds::FACTORY_BG);
    m_bgMusic.setVolume(10);
    m_bgMusic.setLoop(true);
    m_bgMusic.play();
  }

  Factory::~Factory() {
    m_bgMusic.stop();
  }

  void Factory::loadTextures() {
    if (!m_pTextureHolder) {
      std::cerr << "Error loading textures" << std::endl;
      exit(1);
    }

    m_pTextureHolder->load(Textures::StagePlatform, Textures::STRIPPED_PLATFORM_MIDDLE);
    m_pTextureHolder->load(Textures::StagePlatformLeft, Textures::STRIPPED_PLATFORM_LEFT);
    m_pTextureHolder->load(Textures::StagePlatformRight, Textures::STRIPPED_PLATFORM_RIGHT);
    m_pTextureHolder->load(Textures::StageWallLeft, Textures::STRIPPED_WALL_LEFT);
    m_pTextureHolder->load(Textures::StageWallMiddle, Textures::STRIPPED_WALL_MIDDLE);
    m_pTextureHolder->load(Textures::StageWallRight, Textures::STRIPPED_WALL_RIGHT);
    m_pTextureHolder->load(Textures::StageCeiling, Textures::STRIPPED_CEILING_MIDDLE);
    m_pTextureHolder->load(Textures::StageCeilingLeft, Textures::STRIPPED_CEILING_LEFT);
    m_pTextureHolder->load(Textures::StageCeilingRight, Textures::STRIPPED_CEILING_RIGHT);
    m_pTextureHolder->load(Textures::StagePilar, Textures::STRIPPED_PILAR_MIDDLE);
    m_pTextureHolder->load(Textures::StagePilarTop, Textures::STRIPPED_PILAR_TOP);
    m_pTextureHolder->load(Textures::StagePilarBottom, Textures::STRIPPED_PILAR_BOTTOM);

    m_pTextureHolder->load(Textures::Bridge, Textures::FLOATING_STRIPPED_PLATFORM_MIDDLE);
    m_pTextureHolder->load(Textures::BridgeLeft, Textures::FLOATING_STRIPPED_PLATFORM_LEFT);
    m_pTextureHolder->load(Textures::BridgeRight, Textures::FLOATING_STRIPPED_PLATFORM_RIGHT);

    m_pTextureHolder->load(Textures::Spikes, Textures::GROUND_SPIKES);
    m_pTextureHolder->load(Textures::Door, Textures::DOOR);
    m_pTextureHolder->load(Textures::Fly, Textures::FLY_FACTORY);

    m_pTextureHolder->load(Textures::MovingPlatform, Textures::MOVING_PLATFORM);
  }

  void Factory::createTyrant(sf::Vector2f& position) {
    if (m_tyrantNumber >= m_maxTyrantInstances)
      return;

    const int random = 1 + rand() % 100;
    if (random < m_tyrantChance) {
      sf::Texture& textureRef = m_pEntityFactory->getTexture(Textures::Tyrant);
      m_pTyrant = new Entities::Characters::Tyrant(Textures::Tyrant, textureRef, position, static_cast<Stage*>(this));
      m_dynamicEntities.include(static_cast<Entities::Entity*>(m_pTyrant));
    }
  }

  void Factory::createSpring(sf::Vector2f& position) {
    if (m_springNumber >= m_maxSpringInstances)
      return;

    const int random = 1 + rand() % 100;
    if (random < m_springChance) {
      sf::Texture& textureRef = m_pEntityFactory->getTexture(Textures::Spring);
      m_pSpring = new Entities::Obstacles::Spring(Textures::Spring, textureRef, position);
      m_dynamicEntities.include(static_cast<Entities::Entity*>(m_pSpring));
    }
  }

  void Factory::createRandomEnemy(sf::Vector2f& position) {
    sf::Vector2f size = m_pGraphicsManager->getStageSize();

    if (position.y > size.y / 2)
      createGoomba(position);
    else
      createTyrant(position);
  }

  void Factory::createRandomObstacle(sf::Vector2f& position) {
    if (rand() % 2)
      createSpike(position);
    else
      createSpring(position);
  }
}
