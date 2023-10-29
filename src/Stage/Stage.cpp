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

namespace Stages {
  Manager::GraphicsManager* Stage::m_graphicsManager(Manager::GraphicsManager::getInstance());

  Stage::Stage() 
    : m_collisionManager()
    , m_player1()
    , m_platforms()
    , m_paused(false)
  {
    m_collisionManager.setPlayer(&m_player1);
    m_collisionManager.setPlatformsList(&m_platforms);
    createMap();
  }

  Stage::~Stage() {

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
    float x = m_player1.getPosition().x;
    float y = m_player1.getPosition().y;

    if ((x - m_graphicsManager->getViewSize().x/2) < 0)
      x = Constants::WINDOW_WIDTH/2;

    if ((y) + m_graphicsManager->getViewSize().y/2 > Constants::WINDOW_HEIGHT)
      y = Constants::WINDOW_HEIGHT/2;
    
    if (m_player1.getPosition().x < 0) 
      m_player1.setPosition(sf::Vector2f(0.f, m_player1.getPosition().y));
    
    if (m_player1.getPosition().y > Constants::WINDOW_HEIGHT)
      m_player1.setPosition(sf::Vector2f(32.f, 0.f));

    m_graphicsManager->setViewCenter(x, y);
    m_graphicsManager->setView();
  }

  void Stage::update() {
    m_player1.exec();
    m_collisionManager.verifyCollisionPlatforms();
    updateView();
  }

  void Stage::setPaused(const bool paused) {
    m_paused = paused;
  }

  void Stage::exec() {
    if (!m_paused)
      update();
    drawPlatforms();
    m_player1.draw();
  }
}
