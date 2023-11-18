/* Main Include */
#include "Stage/Stage.h"

/* Program Defined */
#include "Entities/Characters/Player.h"
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

  Stage::Stage(const std::string& mapTxt) 
    : m_collisionManager()
    , m_mapTxt(mapTxt)
    , m_players()
    , m_staticEntities()
    , m_dynamicEntities()
    , m_paused(false)
  {
    Entities::Entity::setCollisionManager(&m_collisionManager);
    m_pGraphicsManager->resetTime();

    m_collisionManager.setPlayersList(&m_players);
    m_collisionManager.setStaticEntities(&m_staticEntities);
    m_collisionManager.setDynamicEntities(&m_dynamicEntities);

    m_bgMusic.openFromFile(Sounds::STAGE_BG);
    m_bgMusic.setVolume(10);
    m_bgMusic.setLoop(true);
    m_bgMusic.play();
  }

  Stage::~Stage() {
    
  }

  const std::string& Stage::getMapTxt() const {
    return m_mapTxt;
  } 

  EntityList* Stage::getPlayers() {
    return &m_players;
  }

  EntityList* Stage::getPlatforms() {
    return &m_staticEntities;
  }

  EntityList* Stage::getEnemies() {
    return &m_dynamicEntities;
  }

  void Stage::loadSaveGame() {
    setup();
  }

  void Stage::savePlayerData() {
    nlohmann::ordered_json playerData;
    List<Entities::Entity*>::Iterator playersIterator;

    for (playersIterator = m_players.first(); playersIterator != m_players.last(); ++playersIterator)
      (*playersIterator)->save(playerData);

    std::ofstream jsonOut("saves/player.json");
    jsonOut << std::setw(2) << playerData;
    jsonOut.close();
  }

  void Stage::saveEntitiesData() {
    nlohmann::ordered_json entitiesData;
    List<Entities::Entity*>::Iterator entitiesIterator;

    for (entitiesIterator = m_staticEntities.first(); entitiesIterator != m_staticEntities.last(); ++entitiesIterator)
      (*entitiesIterator)->save(entitiesData);

    for (entitiesIterator = m_dynamicEntities.first(); entitiesIterator != m_dynamicEntities.last(); ++entitiesIterator)
      (*entitiesIterator)->save(entitiesData);

    std::ofstream jsonOut("saves/entities.json");
    jsonOut << std::setw(2) << entitiesData;
    jsonOut.close();
  }

  void Stage::saveGame() {
    savePlayerData();
    saveEntitiesData();
  }

  void Stage::applyPhysics(Entities::Entity* pEntity) {
    sf::Vector2f velocity = pEntity->getVelocity();

    // Gravity
    velocity.y += Constants::GRAVITY * m_dt;
    if (velocity.y > Constants::MAX_FALL_SPEED)
      velocity.y = Constants::MAX_FALL_SPEED;

    // Drag
    if (pEntity->getIsStaggered()) {
      if (velocity.x > 0)
        velocity.x -= Constants::DRAG * m_dt;
      else if (velocity.x < 0)
        velocity.x += Constants::DRAG * m_dt;
    }

    pEntity->setVelocity(velocity);
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
      updateEntities(m_dynamicEntities);
      updateEntities(m_players);
      m_collisionManager.verifyCollisions();
      (*timeSinceLastUpdate) -= (*timePerFrame);
    }

    Entities::Characters::Player* player1 = static_cast<Entities::Characters::Player*>(*(m_players.first()));
    m_pGraphicsManager->updateView(player1->getPosition().x, player1->getPosition().y);
  }

  void Stage::setPaused(const bool paused) {
    m_paused = paused;
  }

  void Stage::exec() {
    if (!m_paused)
      update();
    drawEntities(m_staticEntities);
    drawEntities(m_dynamicEntities);
    drawEntities(m_players);
  }
}
