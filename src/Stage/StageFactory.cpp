/* Main Include */
#include "Stage/StageFactory.h"

/* Program Defined */
#include "Entities/Entity.h"
#include "Entities/EntityFactory.h"
#include "Stage/Cave.h"
#include "Stage/Factory.h"
#include "Stage/Stage.h"
#include "State/GameState.h"
#include "Entities/Characters/Goomba.h"
#include "Entities/Obstacles/Platform.h"
#include "Manager/GraphicsManager.h"
#include "Utility/Constants.h"

/* SFML Library */
#include <SFML/Graphics.hpp>

/* Standard Library */
#include <fstream>
#include <iostream>
#include <string>

/* JSON Library */
#include "nlohmann/json.hpp"

namespace Stages {
  Manager::GraphicsManager* StageFactory::m_graphicsManager(Manager::GraphicsManager::getInstance());

  StageFactory::StageFactory(const bool newGame, const bool multiplayer)
    : m_newGame(newGame)
    , m_entityFactory()
    , m_textureHolder()
    , m_soundHolder()
    , m_pStage(NULL)
    , m_multiplayer(multiplayer)
  {
    loadTextures();
    loadSounds();

    m_entityFactory.setTextureHolder(&m_textureHolder);
    m_entityFactory.setSoundHolder(&m_soundHolder);
  }

  StageFactory::~StageFactory() {
    m_pStage = NULL;
  }

  void StageFactory::loadTextures() {
    m_textureHolder.load(Textures::Player1, Textures::PLAYER1);
    m_textureHolder.load(Textures::Player2, Textures::PLAYER2);

    m_textureHolder.load(Textures::Goomba, Textures::GOOMBA);
    m_textureHolder.load(Textures::Fly, Textures::FLY);
    m_textureHolder.load(Textures::Tyrant, Textures::TYRANT);
    m_textureHolder.load(Textures::Enemy3, Textures::ENEMY3);
    m_textureHolder.load(Textures::Projectile, Textures::PROJECTILE);

    m_textureHolder.load(Textures::Platform, Textures::PLATFORM);
    m_textureHolder.load(Textures::PlatformLeft, Textures::PLATFORM_LEFT_CORNER);
    m_textureHolder.load(Textures::PlatformLeftB, Textures::PLATFORM_LEFT_CORNER_BLACK);
    m_textureHolder.load(Textures::PlatformRight, Textures::PLATFORM_RIGHT_CORNER);
    m_textureHolder.load(Textures::PlatformRightB, Textures::PLATFORM_RIGHT_CORNER_BLACK);

    m_textureHolder.load(Textures::BeltLeft, Textures::BELT_LEFT);
    m_textureHolder.load(Textures::BeltMiddle, Textures::BELT_MIDDLE);
    m_textureHolder.load(Textures::BeltRight, Textures::BELT_RIGHT);

    m_textureHolder.load(Textures::StrippedPlatformLeft, Textures::STRIPPED_PLATFORM_LEFT);
    m_textureHolder.load(Textures::StrippedPlatformMiddle, Textures::STRIPPED_PLATFORM_MIDDLE);
    m_textureHolder.load(Textures::StrippedPlatformRight, Textures::STRIPPED_PLATFORM_RIGHT);

    m_textureHolder.load(Textures::Spikes, Textures::GROUND_SPIKES);

    m_textureHolder.load(Textures::MovingPlatform, Textures::MOVING_PLATFORM);
  }

  void StageFactory::loadSounds() {
    m_soundHolder.load(Sounds::playerJump, Sounds::PLAYER_JUMP);
  }

  Stage* StageFactory::createStage(States::GameState* pGameState, Stages::ID stageID) {
    srand(time(NULL));

    switch (stageID) {
      case CaveID:
        m_pStage = new Cave(pGameState);
        break;
      case FactoryID:
        m_pStage = new Factory(pGameState);
        break;
      default: break;
    }

    if (!m_pStage) {
      std::cerr << "Error creating stage!" << std::endl;
      exit(1);
    }

    m_pPlayers = m_pStage->getPlayers();
    m_pStaticEntities = m_pStage->getStaticEntities();
    m_pDynamicEntities = m_pStage->getDynamicEntities();
    m_pStage->setEntityFactory(&m_entityFactory);

    if (m_newGame) {
      createMap(m_pStage->getMapTxt());
      createPlayers();
    } else {
      loadSaveGame();
    }
    
    return m_pStage;
  }

  void StageFactory::loadPlayerData() {
    using namespace nlohmann;
    using namespace Entities;

    std::ifstream playerStream("saves/player.json");
    ordered_json playerData = ordered_json::parse(playerStream);

    ordered_json::iterator it = playerData.begin();
    
    Characters::Player* pPlayer = new Characters::Player(m_textureHolder.getResource(Textures::Player1), m_soundHolder.getResource(Sounds::playerJump));
    pPlayer->loadSave(*it);
    m_pPlayers->include(pPlayer);
    ++it;

    if (it != playerData.end()) {
      pPlayer = new Characters::Player(m_textureHolder.getResource(Textures::Player2), m_soundHolder.getResource(Sounds::playerJump), sf::Keyboard::Left, sf::Keyboard::Right, sf::Keyboard::Up);
      pPlayer->loadSave(*it);
      m_pPlayers->include(pPlayer);
    }

    playerStream.close();
  }

  void StageFactory::loadEntitiesData() {
    using namespace nlohmann;
    using namespace Entities;

    std::ifstream entitiesStream("saves/entities.json");
    ordered_json entitiesData = ordered_json::parse(entitiesStream);

    ordered_json::iterator it;
    Entity* pEntity = NULL;
    sf::Vector2f position;

    for (it = entitiesData.begin(); it != entitiesData.end(); ++it) {
      position.x = (*it)["position"]["x"].template get<float>();
      position.y = (*it)["position"]["y"].template get<float>();
      pEntity = m_entityFactory.createEntity((*it)["ID"].template get<EntityID>(), (*it)["textureID"].template get<Textures::ID>(), position, m_pStage);
      pEntity->loadSave(*it);
      defineType(pEntity);
    }

    entitiesStream.close();
  }

  void StageFactory::loadSaveGame() {
    loadPlayerData();
    loadEntitiesData();
  }

  void StageFactory::defineType(Entities::Entity* pEntity) {
    using namespace Entities;

    EntityType group = pEntity->getEntityType();

    switch (group) {
      case (EntityType::Static):
        m_pStaticEntities->include(pEntity);
        break;
      case (EntityType::Dynamic):
        m_pDynamicEntities->include(pEntity);
        break;
    }
  }

  void StageFactory::createPlayers() {
    m_pPlayers->include(new Entities::Characters::Player(m_textureHolder.getResource(Textures::Player1), m_soundHolder.getResource(Sounds::playerJump)));
    if (m_multiplayer)
      m_pPlayers->include(new Entities::Characters::Player(m_textureHolder.getResource(Textures::Player2), m_soundHolder.getResource(Sounds::playerJump), sf::Keyboard::Left, sf::Keyboard::Right, sf::Keyboard::Up));
    
    sf::Vector2f playerPosition = sf::Vector2f();
    playerPosition.x = Constants::WINDOW_WIDTH / 2;
    playerPosition.y = (m_graphicsManager->getStageSize().y - (10.f * Constants::TILE_SIZE));

    List<Entities::Entity*>::Iterator it = m_pPlayers->first();
    while (it != m_pPlayers->last()) {
      (*it)->setPosition(playerPosition);
      ++it;
    }
  }

  void StageFactory::createMap(const std::string& stageTxt) {
    std::ifstream stage(stageTxt.c_str());

    if (!stage) {
      std::cout << "Error loading stage\n";
      exit(24);
    }
      
    int i, j;
    std::string line;
    sf::Vector2f position = sf::Vector2f();

    for (i = 0; std::getline(stage, line); ++i) {
      for (j = 0; j < line.size(); ++j) {
        position.x = j * Constants::TILE_SIZE;
        position.y = i * Constants::TILE_SIZE;

        switch (line[j]) {
          case ('P'): defineType(m_entityFactory.createEntity(Entities::PlatformE, Textures::Platform, position)); break;
          case ('A'): defineType(m_entityFactory.createEntity(Entities::PlatformE, Textures::PlatformLeft, position)); break;
          case ('B'): defineType(m_entityFactory.createEntity(Entities::PlatformE, Textures::PlatformRight, position)); break;
          case ('C'): defineType(m_entityFactory.createEntity(Entities::PlatformE, Textures::PlatformLeftB, position)); break;
          case ('D'): defineType(m_entityFactory.createEntity(Entities::PlatformE, Textures::PlatformRightB, position)); break;
          case ('X'): defineType(m_entityFactory.createEntity(Entities::PlatformE, Textures::BeltLeft, position)); break;
          case ('Y'): defineType(m_entityFactory.createEntity(Entities::PlatformE, Textures::BeltMiddle, position)); break;
          case ('Z'): defineType(m_entityFactory.createEntity(Entities::PlatformE, Textures::BeltRight, position)); break;
          case ('S'): defineType(m_entityFactory.createEntity(Entities::PlatformE, Textures::StrippedPlatformLeft, position)); break;
          case ('O'): defineType(m_entityFactory.createEntity(Entities::PlatformE, Textures::StrippedPlatformMiddle, position)); break;
          case ('Q'): defineType(m_entityFactory.createEntity(Entities::PlatformE, Textures::StrippedPlatformRight, position)); break;
          case ('E'): defineType(m_entityFactory.createEntity(Entities::GoombaE, Textures::Goomba, position)); break;
          case ('F'): defineType(m_entityFactory.createEntity(Entities::FlyE, Textures::Fly, position)); break;
          case ('G'): defineType(m_entityFactory.createEntity(Entities::EnemyE, Textures::Enemy3, position)); break;
          case ('T'): defineType(m_entityFactory.createEntity(Entities::TyrantE, Textures::Tyrant, position, m_pStage)); break;
          case ('M'): defineType(m_entityFactory.createEntity(Entities::MovingPlatformE, Textures::MovingPlatform, position)); break;
          case ('I'): defineType(m_entityFactory.createEntity(Entities::SpikesE, Textures::Spikes, position)); break;
          case ('R'): m_pStage->createRandomEnemy(position); break;
          default: break;
        }
      }
    }

    stage.close();
    m_graphicsManager->setStageSize(i * Constants::TILE_SIZE, j * Constants::TILE_SIZE);
  }
}
