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
    m_textureHolder.load(Textures::Tyrant, Textures::TYRANT);
    m_textureHolder.load(Textures::Projectile, Textures::PROJECTILE);

    m_textureHolder.load(Textures::Platform, Textures::PLATFORM);
    m_textureHolder.load(Textures::PlatformLeft, Textures::PLATFORM_LEFT_CORNER);
    m_textureHolder.load(Textures::PlatformLeftB, Textures::PLATFORM_LEFT_CORNER_BLACK);
    m_textureHolder.load(Textures::PlatformRight, Textures::PLATFORM_RIGHT_CORNER);
    m_textureHolder.load(Textures::PlatformRightB, Textures::PLATFORM_RIGHT_CORNER_BLACK);

    m_textureHolder.load(Textures::PipeTopLeft, Textures::PIPE_TOP_LEFT);
    m_textureHolder.load(Textures::PipeTopRight, Textures::PIPE_TOP_RIGHT);
    m_textureHolder.load(Textures::PipeBottomLeft, Textures::PIPE_BOTTOM_LEFT);
    m_textureHolder.load(Textures::PipeBottomRight, Textures::PIPE_BOTTOM_RIGHT);
    m_textureHolder.load(Textures::PipeHorizontal, Textures::PIPE_HORIZONTAL);
    m_textureHolder.load(Textures::PipeVertical, Textures::PIPE_VERTICAL);
    m_textureHolder.load(Textures::PipeHorizontalBroken, Textures::PIPE_HORIZONTAL_BROKEN);
    m_textureHolder.load(Textures::PipeVerticalBroken, Textures::PIPE_VERTICAL_BROKEN);

    m_textureHolder.load(Textures::Door, Textures::DOOR);
    m_textureHolder.load(Textures::Spring, Textures::SPRING);
    m_textureHolder.load(Textures::Flag, Textures::FLAG);
    m_textureHolder.load(Textures::Coin, Textures::COIN);
  }

  void StageFactory::loadSounds() {
    m_soundHolder.load(Sounds::playerJump, Sounds::PLAYER_JUMP);
    m_soundHolder.load(Sounds::Coin, Sounds::COIN);
    m_soundHolder.load(Sounds::Save, Sounds::SAVE);
  }

  Stage* StageFactory::createStage(States::GameState* pGameState, Stages::ID stageID, const bool multiplayer) {
    srand(time(NULL));
    m_multiplayer = multiplayer;

    switch (stageID) {
      case CaveID:
        m_pStage = new Cave(&m_textureHolder, &m_entityFactory, pGameState);
        break;
      case FactoryID:
        m_pStage = new Factory(&m_textureHolder, &m_entityFactory, pGameState);
        break;
      default: break;
    }

    if (!m_pStage) {
      std::cerr << "Error creating stage!" << std::endl;
      exit(1);
    }

    m_pStage->loadTextures();
    m_pPlayers = m_pStage->getPlayers();
    m_pStaticEntities = m_pStage->getStaticEntities();
    m_pDynamicEntities = m_pStage->getDynamicEntities();
    m_pViews = m_pStage->getViews();
    createViews();

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

    std::ifstream playerStream("saves/players.json");
    if (!playerStream)
      throw -1;

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
    if (!entitiesStream)
      throw -2;

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
    try {
      loadPlayerData();
      loadEntitiesData();
    } catch (int err) {
      switch (err) {
        case -1: 
          std::cerr << "Error loading players data!" << std::endl;
          break;
        case -2:
          std::cerr << "Error loading entities data!" << std::endl;
          break;
        default: break;
      }
    }
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

  void StageFactory::createViews() {
    m_pViews->push_back(sf::View(sf::Vector2f(0.f, 0.f), sf::Vector2f(static_cast<float>(Constants::WINDOW_WIDTH), static_cast<float>(Constants::WINDOW_HEIGHT))));

    if (m_multiplayer) {
      (*m_pViews)[0].setViewport(sf::FloatRect(0.f, 0.f, 0.5f, 1.f));
      (*m_pViews)[0].setSize(Constants::WINDOW_WIDTH/2, Constants::WINDOW_HEIGHT);
      m_pViews->push_back(sf::View(sf::Vector2f(0.f, 0.f), sf::Vector2f(static_cast<float>(Constants::WINDOW_WIDTH/2), static_cast<float>(Constants::WINDOW_HEIGHT))));
      (*m_pViews)[1].setViewport(sf::FloatRect(0.5f, 0.f, 0.5f, 1.f));
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
          case ('-'): defineType(m_entityFactory.createEntity(Entities::PlatformE, Textures::Platform, position)); break;
          case ('<'): defineType(m_entityFactory.createEntity(Entities::PlatformE, Textures::PlatformLeft, position)); break;
          case ('>'): defineType(m_entityFactory.createEntity(Entities::PlatformE, Textures::PlatformRight, position)); break;
          case ('['): defineType(m_entityFactory.createEntity(Entities::PlatformE, Textures::PlatformLeftB, position)); break;
          case (']'): defineType(m_entityFactory.createEntity(Entities::PlatformE, Textures::PlatformRightB, position)); break;

          case ('('): defineType(m_entityFactory.createEntity(Entities::PlatformE, Textures::StagePlatformLeft, position)); break;
          case ('='): defineType(m_entityFactory.createEntity(Entities::PlatformE, Textures::StagePlatform, position)); break;
          case (')'): defineType(m_entityFactory.createEntity(Entities::PlatformE, Textures::StagePlatformRight, position)); break;
          case ('{'): defineType(m_entityFactory.createEntity(Entities::PlatformE, Textures::StageWallLeft, position)); break;
          case ('@'): defineType(m_entityFactory.createEntity(Entities::PlatformE, Textures::StageWallMiddle, position)); break;
          case ('}'): defineType(m_entityFactory.createEntity(Entities::PlatformE, Textures::StageWallRight, position)); break;
          case ('L'): defineType(m_entityFactory.createEntity(Entities::PlatformE, Textures::StageCeilingLeft, position)); break;
          case ('_'): defineType(m_entityFactory.createEntity(Entities::PlatformE, Textures::StageCeiling, position)); break;
          case ('J'): defineType(m_entityFactory.createEntity(Entities::PlatformE, Textures::StageCeilingRight, position)); break;
          case ('A'): defineType(m_entityFactory.createEntity(Entities::PlatformE, Textures::StagePilarTop, position)); break;
          case ('B'): defineType(m_entityFactory.createEntity(Entities::PlatformE, Textures::StagePilar, position)); break;
          case ('C'): defineType(m_entityFactory.createEntity(Entities::PlatformE, Textures::StagePilarBottom, position)); break;

          case ('X'): defineType(m_entityFactory.createEntity(Entities::PlatformE, Textures::BridgeLeft, position)); break;
          case ('Y'): defineType(m_entityFactory.createEntity(Entities::PlatformE, Textures::Bridge, position)); break;
          case ('Z'): defineType(m_entityFactory.createEntity(Entities::PlatformE, Textures::BridgeRight, position)); break;

          case ('7'): defineType(m_entityFactory.createEntity(Entities::PlatformE, Textures::PipeTopLeft, position)); break;
          case ('8'): defineType(m_entityFactory.createEntity(Entities::PlatformE, Textures::PipeHorizontal, position)); break;
          case ('9'): defineType(m_entityFactory.createEntity(Entities::PlatformE, Textures::PipeTopRight, position)); break;
          case ('4'): defineType(m_entityFactory.createEntity(Entities::PlatformE, Textures::PipeVertical, position)); break;
          case ('6'): defineType(m_entityFactory.createEntity(Entities::PlatformE, Textures::PipeVerticalBroken, position)); break;
          case ('1'): defineType(m_entityFactory.createEntity(Entities::PlatformE, Textures::PipeBottomLeft, position)); break;
          case ('2'): defineType(m_entityFactory.createEntity(Entities::PlatformE, Textures::PipeHorizontalBroken, position)); break;
          case ('3'): defineType(m_entityFactory.createEntity(Entities::PlatformE, Textures::PipeBottomRight, position)); break;

          case ('G'): defineType(m_entityFactory.createEntity(Entities::GoombaE, Textures::Goomba, position)); break;
          case ('F'): defineType(m_entityFactory.createEntity(Entities::FlyE, Textures::Fly, position)); break;
          case ('T'): defineType(m_entityFactory.createEntity(Entities::TyrantE, Textures::Tyrant, position, m_pStage)); break;
          case ('M'): defineType(m_entityFactory.createEntity(Entities::MovingPlatformE, Textures::MovingPlatform, position)); break;
          case ('^'): defineType(m_entityFactory.createEntity(Entities::SpikesE, Textures::Spikes, position)); break;
          case ('D'): defineType(m_entityFactory.createEntity(Entities::DoorE, Textures::Door, position)); break;
          case ('S'): defineType(m_entityFactory.createEntity(Entities::SpringE, Textures::Spring, position)); break;
          case ('Q'): defineType(m_entityFactory.createEntity(Entities::FlagE, Textures::Flag, position, m_pStage)); break;
          case ('R'): defineType(m_entityFactory.createEntity(Entities::CoinE, Textures::Coin, position, m_pStage)); break;
          case ('E'): m_pStage->createRandomEnemy(position); break;
          case ('O'): m_pStage->createRandomObstacle(position); break;
          default: break;
        }
      }
    }

    stage.close();
    m_graphicsManager->setStageSize(i * Constants::TILE_SIZE, j * Constants::TILE_SIZE);
  }
}
