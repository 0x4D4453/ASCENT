/* Main Include */
#include "Stage/Stage.h"

/* Program Defined */
#include "Entities/Entity.h"
#include "Entities/EntityList.h"
#include "Entities/Goomba.h"
#include "Entities/Platform.h"
#include "Entities/Player.h"
#include "Manager/CollisionManager.h"
#include "Manager/GraphicsManager.h"
#include "Utility/Constants.h"
#include "Utility/List.h"

/* SFML Library */
#include <SFML/Graphics.hpp>

/* Standard Library */
#include <fstream>
#include <iostream>
#include <string>

/* JSON Library */
#include "nlohmann/json.hpp"

namespace Stages {
  Manager::GraphicsManager* Stage::m_graphicsManager(Manager::GraphicsManager::getInstance());

  Stage::Stage(const bool newGame) 
    : m_collisionManager()
    , m_platforms()
    , m_enemies()
    , m_paused(false)
  {
    if (!newGame)
      loadSaveGame();

    Entities::Entity::setCollisionManager(&m_collisionManager);

    m_players.include(new Entities::Player(Constants::PLAYER1_TEXTURE, Constants::PLAYER1_TEXTURE_WALK1, Constants::PLAYER1_TEXTURE_WALK2, Constants::PLAYER1_TEXTURE_WALK3, Constants::PLAYER1_TEXTURE_JUMP));
    m_players.include(new Entities::Player(Constants::PLAYER2_TEXTURE, Constants::PLAYER2_TEXTURE_WALK1, Constants::PLAYER2_TEXTURE_WALK2, Constants::PLAYER2_TEXTURE_WALK3, Constants::PLAYER2_TEXTURE_JUMP, sf::Keyboard::Left, sf::Keyboard::Right, sf::Keyboard::Up));

    m_collisionManager.setPlayersList(&m_players);
    m_collisionManager.setObstaclesList(&m_platforms);
    m_collisionManager.setEnemiesList(&m_enemies);
    
    createMap();
  }

  Stage::~Stage() {

  }

  void Stage::loadSaveGame() {

  }

  void Stage::saveGame() {

  }

  void Stage::createPlatform(const sf::Vector2f position, const char* texture) {
    using namespace Entities;
    Entities::Entity* pEntity = NULL;

    pEntity = static_cast<Entity*>(new Platform(position, texture));

    if (!pEntity) {
      std::cerr << "Error creating platform!\n";
      return;
    }

    m_platforms.include(pEntity);
  }

  void Stage::createEnemy(const sf::Vector2f position, const char* texture) {
    using namespace Entities;
    Entities::Entity* pEntity = NULL;

    pEntity = static_cast<Entity*>(new Goomba(texture, position));

    if (!pEntity) {
      std::cerr << "Error creating enemy!\n";
      return;
    }

    m_enemies.include(pEntity);
  }

  void Stage::createMap() {
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
    setPlayerPosition(i);
  }

  void Stage::setPlayerPosition(int height) {
    sf::Vector2f playerPosition = sf::Vector2f();
    playerPosition.x = Constants::WINDOW_WIDTH / 2;
    playerPosition.y = (height - 10) * Constants::TILE_SIZE;

    List<Entities::Entity*>::Iterator it = m_players.first();
    while (it != m_players.last()) {
      (*it)->setPosition(playerPosition);
      ++it;
    }
  }

  void Stage::drawEntities(EntityList& entityList) {
    List<Entities::Entity*>::Iterator it = entityList.first();
    while (it != entityList.last()) {
      (*it)->draw();
      ++it;
    }
  }

  void Stage::updateEntities(EntityList& entityList) {
    List<Entities::Entity*>::Iterator it = entityList.first();
    while (it != entityList.last()) {
      (*it)->exec();
      ++it;
    }
  }
  
  void Stage::update() {
    sf::Time* timeSinceLastUpdate = m_graphicsManager->getTimeSinceLastUpdate();
    const sf::Time* timePerFrame = m_graphicsManager->getTimePerFrame();

    while (*timeSinceLastUpdate >= *timePerFrame) {
      updateEntities(m_enemies);
      updateEntities(m_players);
      (*timeSinceLastUpdate) -= (*timePerFrame);
    }

    Entities::Player* player1 = static_cast<Entities::Player*>(*(m_players.first()));
    m_graphicsManager->updateView(player1->getPosition().x, player1->getPosition().y);
  }

  void Stage::setPaused(const bool paused) {
    m_paused = paused;
  }

  void Stage::exec() {
    if (!m_paused)
      update();
    drawEntities(m_platforms);
    drawEntities(m_enemies);
    drawEntities(m_players);
  }
}
