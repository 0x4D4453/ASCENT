/* Main Include */
#include "Stage/Stage.h"

/* Program Defined */
#include "Entities/Player.h"
#include "Manager/Collision/CollisionManager.h"
#include "Manager/GraphicsManager.h"
#include "Utility/Constants.h"
#include "Utility/List.h"
#include "Utility/Sounds.h"

/* SFML Library */
#include <SFML/Graphics.hpp>

/* Standard Library */
#include <fstream>
#include <iostream>
#include <string>

/* JSON Library */
#include "nlohmann/json.hpp"

namespace Stages {
  Manager::GraphicsManager* Stage::m_pGraphicsManager(Manager::GraphicsManager::getInstance());
  const float Stage::m_dt(Stage::m_pGraphicsManager->getTimePerFrame()->asSeconds()); 

  Stage::Stage(const bool newGame) 
    : m_collisionManager()
    , m_players()
    , m_platforms()
    , m_enemies()
    , m_paused(false)
  {
    Entities::Entity::setCollisionManager(&m_collisionManager);

    if (!newGame)
      loadSaveGame();

    m_collisionManager.setPlayersList(&m_players);
    m_collisionManager.setObstaclesList(&m_platforms);
    m_collisionManager.setEnemiesList(&m_enemies);

    m_filterRect.setSize(sf::Vector2f(Constants::WINDOW_WIDTH, Constants::WINDOW_HEIGHT));
    m_filterRect.setFillColor(sf::Color(236.f, 236.f, 236.f, 40.f));

    m_pGraphicsManager->setViewPort(sf::FloatRect(0.f, 0.f, 0.5f, 1.f));
    m_pGraphicsManager->setViewSize(Constants::WINDOW_WIDTH/2, Constants::WINDOW_HEIGHT);
    
    m_pGraphicsManager->setViewPort2(sf::FloatRect(0.5f, 0.f, 0.5f, 1.f));
    m_pGraphicsManager->setViewSize2(Constants::WINDOW_WIDTH/2, Constants::WINDOW_HEIGHT);
    
    m_bgMusic.openFromFile(Sounds::STAGE_BG);
    m_bgMusic.setVolume(10);
    m_bgMusic.setLoop(true);
    m_bgMusic.play();
  }

  Stage::~Stage() {
    m_bgMusic.stop();
  }
  
  EntityList* Stage::getPlayers() {
    return &m_players;
  }

  EntityList* Stage::getPlatforms() {
    return &m_platforms;
  }

  EntityList* Stage::getEnemies() {
    return &m_enemies;
  }

  void Stage::loadSaveGame() {
    setup();
  }

  void Stage::saveGame() {

  }

  void Stage::applyPhysics(Entities::Entity* entity) {
    sf::Vector2f velocity = entity->getVelocity();

    // Gravity
    velocity.y += Constants::GRAVITY * m_dt;
    if (velocity.y > Constants::MAX_FALL_SPEED)
      velocity.y = Constants::MAX_FALL_SPEED;

    // Drag
    if (entity->getIsStaggered()) {
      if (velocity.x > 0)
        velocity.x -= Constants::DRAG * m_dt;
      else if (velocity.x < 0)
        velocity.x += Constants::DRAG * m_dt;
    }

    entity->setVelocity(velocity);
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
      applyPhysics((*it));
      (*it)->exec();
      ++it;
    }
  }
  
  void Stage::update() {
    sf::Time* timeSinceLastUpdate = m_pGraphicsManager->getTimeSinceLastUpdate();
    const sf::Time* timePerFrame = m_pGraphicsManager->getTimePerFrame();

    while (*timeSinceLastUpdate >= *timePerFrame) {
      updateEntities(m_enemies);
      updateEntities(m_players);
      (*timeSinceLastUpdate) -= (*timePerFrame);
    }

    Entities::Player* player1 = static_cast<Entities::Player*>(*(m_players.first()));
    Entities::Player* player2 = static_cast<Entities::Player*>(*(++m_players.first()));
    m_pGraphicsManager->updateView(player1->getPosition().x, player1->getPosition().y);
    m_pGraphicsManager->updateView2(player2->getPosition().x, player2->getPosition().y);

    m_filterRect.setPosition(m_pGraphicsManager->getViewCoordinates().x, m_pGraphicsManager->getViewCoordinates().y);
  }

  void Stage::setPaused(const bool paused) {
    m_paused = paused;
  }

  void Stage::drawEverything() {
    m_pGraphicsManager->setView();
    drawEntities(m_platforms);
    drawEntities(m_enemies);
    drawEntities(m_players);
    
    m_pGraphicsManager->setView2();
    drawEntities(m_platforms);
    drawEntities(m_enemies);
    drawEntities(m_players);
  }

  void Stage::exec() {
    if (m_paused)
      return;
    update();
    drawEverything();
  }
}
