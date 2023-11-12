/* Main Include */
#include "Stage/StageFactory.h"

/* Program Defined */
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
    , m_textureHolder()
    , m_soundHolder()
  {
    loadTextures();
    loadSounds();
  }

  StageFactory::~StageFactory() {

  }

  void StageFactory::loadTextures() {
    m_textureHolder.load(Textures::Player1, Textures::PLAYER1);
    m_textureHolder.load(Textures::Player1Walk1, Textures::PLAYER1_WALK1);
    m_textureHolder.load(Textures::Player1Walk2, Textures::PLAYER1_WALK2);
    m_textureHolder.load(Textures::Player1Walk3, Textures::PLAYER1_WALK3);
    m_textureHolder.load(Textures::Player1Charge, Textures::PLAYER1_CHARGE);
    m_textureHolder.load(Textures::Player1Jump, Textures::PLAYER1_JUMP);

    m_textureHolder.load(Textures::Player2, Textures::PLAYER2);
    m_textureHolder.load(Textures::Player2Walk1, Textures::PLAYER2_WALK1);
    m_textureHolder.load(Textures::Player2Walk2, Textures::PLAYER2_WALK2);
    m_textureHolder.load(Textures::Player2Walk3, Textures::PLAYER2_WALK3);
    m_textureHolder.load(Textures::Player2Charge, Textures::PLAYER2_CHARGE);
    m_textureHolder.load(Textures::Player2Jump, Textures::PLAYER2_JUMP);

    m_textureHolder.load(Textures::Goomba, Textures::ENEMY1);
    m_textureHolder.load(Textures::Enemy2, Textures::ENEMY2);
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
  }

  void StageFactory::loadSounds() {
    m_soundHolder.load(Sounds::playerJump, Sounds::PLAYER_JUMP);
  }

  Stage* StageFactory::createStage(const char* stageTxt) {
    Stage* stage = new Stage(m_newGame);

    m_players = stage->getPlayers();
    m_platforms = stage->getPlatforms();
    m_enemies = stage->getEnemies();

    createMap(stageTxt);
    return stage;
  }

  void StageFactory::createPlayers(int stageHeight) {
    m_players->include(new Entities::Player(m_textureHolder.getResource(Textures::Player1), m_textureHolder.getResource(Textures::Player1Walk1), m_textureHolder.getResource(Textures::Player1Walk2), m_textureHolder.getResource(Textures::Player1Walk3), m_textureHolder.getResource(Textures::Player1Jump), m_textureHolder.getResource(Textures::Player1Charge), m_soundHolder.getResource(Sounds::playerJump)));
    m_players->include(new Entities::Player(m_textureHolder.getResource(Textures::Player2), m_textureHolder.getResource(Textures::Player2Walk1), m_textureHolder.getResource(Textures::Player2Walk2), m_textureHolder.getResource(Textures::Player2Walk3), m_textureHolder.getResource(Textures::Player2Jump), m_textureHolder.getResource(Textures::Player2Charge), m_soundHolder.getResource(Sounds::playerJump), sf::Keyboard::Left, sf::Keyboard::Right, sf::Keyboard::Up));
    
    sf::Vector2f playerPosition = sf::Vector2f();
    playerPosition.x = Constants::WINDOW_WIDTH / 2;
    playerPosition.y = (stageHeight - 10) * Constants::TILE_SIZE;

    List<Entities::Entity*>::Iterator it = m_players->first();
    while (it != m_players->last()) {
      (*it)->setPosition(playerPosition);
      ++it;
    }
  }

  void StageFactory::createPlatform(const sf::Vector2f position, Textures::ID textureID) {
    using namespace Entities;
    Entities::Entity* pEntity = NULL;

    pEntity = static_cast<Entity*>(new Platform(m_textureHolder.getResource(textureID), position));

    if (!pEntity) {
      std::cerr << "Error creating platform!\n";
      return;
    }

    m_platforms->include(pEntity);
  }

  void StageFactory::createEnemy(const sf::Vector2f position, Textures::ID textureID) {
    using namespace Entities;
    Entities::Entity* pEntity = NULL;

    pEntity = static_cast<Entity*>(new Goomba(m_textureHolder.getResource(textureID), position));

    if (!pEntity) {
      std::cerr << "Error creating enemy!\n";
      return;
    }

    m_enemies->include(pEntity);
  }

  void StageFactory::createMap(const char* stageTxt) {
    std::ifstream stage("assets/stage_2.txt");

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
          case ('P'): createPlatform(position, Textures::Platform); break;
          case ('A'): createPlatform(position, Textures::PlatformLeft); break;
          case ('B'): createPlatform(position, Textures::PlatformRight); break;
          case ('C'): createPlatform(position, Textures::PlatformLeftB); break;
          case ('D'): createPlatform(position, Textures::PlatformRightB); break;
          case ('X'): createPlatform(position, Textures::BeltLeft); break;
          case ('Y'): createPlatform(position, Textures::BeltMiddle); break;
          case ('Z'): createPlatform(position, Textures::BeltRight); break;
          case ('S'): createPlatform(position, Textures::StrippedPlatformLeft); break;
          case ('O'): createPlatform(position, Textures::StrippedPlatformMiddle); break;
          case ('Q'): createPlatform(position, Textures::StrippedPlatformRight); break;
          case ('E'): createEnemy(position, Textures::Goomba); break;
          case ('F'): createEnemy(position, Textures::Enemy2); break;
          case ('G'): createEnemy(position, Textures::Enemy3); break;
          default: break;
        }
      }
    }

    stage.close();

    m_graphicsManager->setStageSize((i - 1) * Constants::TILE_SIZE, (j - 1) * Constants::TILE_SIZE);
    createPlayers(i);
  }
}
