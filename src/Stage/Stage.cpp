/* Main Include */
#include "Stage/Stage.h"

/* Program Defined */
#include "Entities/Entity.h"
#include "Entities/EntityList.h"
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
    , m_paused(false)
  {
    if (!newGame)
      loadSaveGame();

    Entities::Entity::setCollisionManager(&m_collisionManager);

    m_players.include(new Entities::Player(Constants::PLAYER1_TEXTURE));
    m_players.include(new Entities::Player(Constants::PLAYER2_TEXTURE, sf::Keyboard::Left, sf::Keyboard::Right, sf::Keyboard::Up));

    m_collisionManager.setPlayersList(&m_players);
    m_collisionManager.setObstaclesList(&m_platforms);
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

  void Stage::drawPlatforms() {
    List<Entities::Entity*>::Iterator it = m_platforms.first();
    while (it != m_platforms.last()) {
      (*it)->draw();
      ++it;
    }
  }

  void Stage::drawPlayers() {
    List<Entities::Entity*>::Iterator it = m_players.first();
    while (it != m_players.last()) {
      (*it)->draw();
      ++it;
    }
  }

  void Stage::createMap() {
    std::ifstream stage("assets/stage_1.txt");

    if (!stage) {
      std::cout << "Error loading stage\n";
      exit(24);
    }
      
    std::string line;

    for (int i = 0; std::getline(stage, line); ++i) {
      for (int j = 0; j < line.size(); ++j) {
        sf::Vector2f position(j * Constants::TILE_SIZE, i * Constants::TILE_SIZE);

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
          case ('E'): createPlatform(position, Constants::ENEMY1_TEXTURE); break;
          case ('F'): createPlatform(position, Constants::ENEMY2_TEXTURE); break;
          case ('G'): createPlatform(position, Constants::ENEMY3_TEXTURE); break;
          default: break;
        }
      }
    }

    stage.close();
  }

  void Stage::updateView() {
    Entities::Player* player1 = static_cast<Entities::Player*>(*(m_players.first()));
    Entities::Player* player2 = static_cast<Entities::Player*>(*++((m_players.first())));

    float x = player1->getPosition().x;
    float y = player1->getPosition().y;

    if ((x - m_graphicsManager->getViewSize().x/2) < 0)
      x = Constants::WINDOW_WIDTH/2;

    if ((y+ m_graphicsManager->getViewSize().y/2) > Constants::WINDOW_HEIGHT)
      y = Constants::WINDOW_HEIGHT/2;
    
    if (player1->getPosition().x < 0) 
      player1->setPosition(sf::Vector2f(0.f, player1->getPosition().y));
    
    if (player1->getPosition().y > Constants::WINDOW_HEIGHT)
      player1->setPosition(sf::Vector2f(Constants::TILE_SIZE, 0.f));
    
    if (player2->getPosition().y > Constants::WINDOW_HEIGHT)
      player2->setPosition(sf::Vector2f(Constants::TILE_SIZE, 0.f));

    m_graphicsManager->setViewCenter(x, y);
    m_graphicsManager->setView();
  }

  void Stage::updatePlayers() {
    List<Entities::Entity*>::Iterator it = m_players.first();
    while (it != m_players.last()) {
      (*it)->exec();
      ++it;
    }
  }

  void Stage::update() {
    sf::Time* timeSinceLastUpdate = m_graphicsManager->getTimeSinceLastUpdate();
    const sf::Time* timePerFrame = m_graphicsManager->getTimePerFrame();

    while (*timeSinceLastUpdate >= *timePerFrame) {
      updatePlayers();
      (*timeSinceLastUpdate) -= (*timePerFrame);
    }

    updateView();
  }

  void Stage::setPaused(const bool paused) {
    m_paused = paused;
  }

  void Stage::exec() {
    if (!m_paused)
      update();
    drawPlatforms();
    drawPlayers();
  }
}
