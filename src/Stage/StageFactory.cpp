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
  {

  }

  StageFactory::~StageFactory() {

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
    m_players->include(new Entities::Player(Constants::PLAYER1_TEXTURE, Constants::PLAYER1_TEXTURE_WALK1, Constants::PLAYER1_TEXTURE_WALK2, Constants::PLAYER1_TEXTURE_WALK3, Constants::PLAYER1_TEXTURE_JUMP));
    m_players->include(new Entities::Player(Constants::PLAYER2_TEXTURE, Constants::PLAYER2_TEXTURE_WALK1, Constants::PLAYER2_TEXTURE_WALK2, Constants::PLAYER2_TEXTURE_WALK3, Constants::PLAYER2_TEXTURE_JUMP, sf::Keyboard::Left, sf::Keyboard::Right, sf::Keyboard::Up));
    
    sf::Vector2f playerPosition = sf::Vector2f();
    playerPosition.x = Constants::WINDOW_WIDTH / 2;
    playerPosition.y = (stageHeight - 10) * Constants::TILE_SIZE;

    List<Entities::Entity*>::Iterator it = m_players->first();
    while (it != m_players->last()) {
      (*it)->setPosition(playerPosition);
      ++it;
    }
  }

  void StageFactory::createPlatform(const sf::Vector2f position, const char* texture) {
    using namespace Entities;
    Entities::Entity* pEntity = NULL;

    pEntity = static_cast<Entity*>(new Platform(position, texture));

    if (!pEntity) {
      std::cerr << "Error creating platform!\n";
      return;
    }

    m_platforms->include(pEntity);
  }

  void StageFactory::createEnemy(const sf::Vector2f position, const char* texture) {
    using namespace Entities;
    Entities::Entity* pEntity = NULL;

    pEntity = static_cast<Entity*>(new Goomba(texture, position));

    if (!pEntity) {
      std::cerr << "Error creating enemy!\n";
      return;
    }

    m_enemies->include(pEntity);
  }

  void StageFactory::createMap(const char* stageTxt) {
    std::ifstream stage(stageTxt);

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
          case ('P'): createPlatform(position, Constants::PLATFORM_TEXTURE); break;
          case ('A'): createPlatform(position, Constants::PLATFORM_TEXTURE_LEFT_CORNER); break;
          case ('B'): createPlatform(position, Constants::PLATFORM_TEXTURE_RIGHT_CORNER); break;
          case ('C'): createPlatform(position, Constants::PLATFORM_TEXTURE_LEFT_CORNER_BLACK); break;
          case ('D'): createPlatform(position, Constants::PLATFORM_TEXTURE_RIGHT_CORNER_BLACK); break;
          case ('X'): createPlatform(position, Constants::BELT_TEXTURE_LEFT); break;
          case ('Y'): createPlatform(position, Constants::BELT_TEXTURE_MIDDLE); break;
          case ('Z'): createPlatform(position, Constants::BELT_TEXTURE_RIGHT); break;
          case ('S'): createPlatform(position, Constants::STRIPPED_PLATFORM_TEXTURE_LEFT); break;
          case ('O'): createPlatform(position, Constants::STRIPPED_PLATFORM_TEXTURE_MIDDLE); break;
          case ('Q'): createPlatform(position, Constants::STRIPPED_PLATFORM_TEXTURE_RIGHT); break;
          case ('E'): createEnemy(position, Constants::ENEMY1_TEXTURE); break;
          case ('F'): createEnemy(position, Constants::ENEMY2_TEXTURE); break;
          case ('G'): createEnemy(position, Constants::ENEMY3_TEXTURE); break;
          default: break;
        }
      }
    }

    stage.close();

    m_graphicsManager->setStageSize((i - 1) * Constants::TILE_SIZE, (j - 1) * Constants::TILE_SIZE);
    createPlayers(i);
  }
}
