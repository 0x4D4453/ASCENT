/* Main Include */
#include "Stage/StageFactory.h"

/* Program Defined */
#include "Entities/Entity.h"
#include "Entities/EntityFactory.h"
#include "Stage/FirstStage.h"
#include "Entities/Goomba.h"
#include "Entities/Platform.h"
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

  StageFactory::StageFactory(const bool newGame)
    : m_newGame(newGame)
    , m_entityFactory()
    , m_textureHolder()
    , m_soundHolder()
  {
    loadTextures();
    loadSounds();

    m_entityFactory.setTextureHolder(&m_textureHolder);
    m_entityFactory.setSoundHolder(&m_soundHolder);
  }

  StageFactory::~StageFactory() {

  }

  void StageFactory::loadTextures() {
    m_textureHolder.load(Textures::Player1, Textures::PLAYER1);
    m_textureHolder.load(Textures::Player2, Textures::PLAYER2);

    m_textureHolder.load(Textures::Goomba, Textures::GOOMBA);
    m_textureHolder.load(Textures::Fly, Textures::FLY);
    m_textureHolder.load(Textures::Enemy3, Textures::ENEMY3);

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
  }

  void StageFactory::loadSounds() {
    m_soundHolder.load(Sounds::playerJump, Sounds::PLAYER_JUMP);
  }

  Stage* StageFactory::createStage(const char* stageTxt) {
    Stage* stage = new FirstStage(m_newGame);

    m_players = stage->getPlayers();
    m_staticEntities = stage->getPlatforms();
    m_dynamicEntities = stage->getEnemies();

    createMap(stageTxt);
    return stage;
  }

  void StageFactory::defineType(Entities::Entity* pEntity) {
    using namespace Entities;

    EntityType group = pEntity->getEntityType();

    switch (group) {
      case (EntityType::Static):
        m_staticEntities->include(pEntity);
        break;
      case (EntityType::Dynamic):
        m_dynamicEntities->include(pEntity);
        break;
    }
  }

  void StageFactory::createPlayers(int stageHeight) {
    m_players->include(new Entities::Player(m_textureHolder.getResource(Textures::Player1), m_soundHolder.getResource(Sounds::playerJump)));
    // m_players->include(new Entities::Player(m_textureHolder.getResource(Textures::Player2), m_soundHolder.getResource(Sounds::playerJump), sf::Keyboard::Left, sf::Keyboard::Right, sf::Keyboard::Up));
    
    sf::Vector2f playerPosition = sf::Vector2f();
    playerPosition.x = Constants::WINDOW_WIDTH / 2;
    playerPosition.y = (stageHeight - 10) * Constants::TILE_SIZE;

    List<Entities::Entity*>::Iterator it = m_players->first();
    while (it != m_players->last()) {
      (*it)->setPosition(playerPosition);
      ++it;
    }
  }

  void StageFactory::createMap(const char* stageTxt) {
    std::ifstream stage("assets/stage_3.txt");

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
          default: break;
        }
      }
    }

    stage.close();

    m_graphicsManager->setStageSize(i * Constants::TILE_SIZE, j * Constants::TILE_SIZE);
    createPlayers(i);
  }
}
