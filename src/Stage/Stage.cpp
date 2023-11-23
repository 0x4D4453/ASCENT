/* Main Include */
#include "Stage/Stage.h"

/* Program Defined */
#include "Entities/Characters/Player.h"
#include "Entities/Characters/Enemy.h"
#include "Entities/EntityFactory.h"
#include "Manager/Collision/CollisionManager.h"
#include "Manager/GraphicsManager.h"
#include "State/GameState.h"
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

  Stage::Stage(ResourceHolder<Textures::ID, sf::Texture>* pTextureHolder, Entities::EntityFactory* pEntityFactory, States::GameState* pGameState, const std::string& mapTxt) 
    : m_collisionManager()
    , m_pTextureHolder(pTextureHolder)
    , m_pEntityFactory(pEntityFactory)
    , m_pGameState(pGameState)
    , m_mapTxt(mapTxt)
    , m_players()
    , m_staticEntities()
    , m_dynamicEntities()
    , m_dynamicDeletionQueue()
    , m_views()
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
    deleteEntitiesInQueue();
    m_pTextureHolder = NULL;
    m_pEntityFactory = NULL;
    m_pGameState = NULL;
  }

  const std::string& Stage::getMapTxt() const {
    return m_mapTxt;
  }

  EntityList* Stage::getPlayers() {
    return &m_players;
  }

  EntityList* Stage::getStaticEntities() {
    return &m_staticEntities;
  }

  EntityList* Stage::getDynamicEntities() {
    return &m_dynamicEntities;
  }

  std::vector<sf::View>* Stage::getViews() {
    return &m_views;
  }

  void Stage::spawnProjectile(Textures::ID textureID, sf::Vector2f& position, const float scale, const float speed, const float angle) {
    Entities::Projectile* projectile = m_pEntityFactory->createProjectile(textureID, position, scale, speed, angle);
    m_dynamicEntities.include(static_cast<Entities::Entity*>(projectile));
    projectile->setStage(this);
  }

  void Stage::addToDeletionList(Entities::Entity* pEntity) {
    m_dynamicDeletionQueue.push(pEntity);
  }

  void Stage::deleteEntitiesInQueue() {
    while (!m_dynamicDeletionQueue.empty()) {
      Entities::Entity* pEntity = m_dynamicDeletionQueue.front();
      m_dynamicEntities.remove(pEntity);
      m_dynamicDeletionQueue.pop();

      delete pEntity;
    }
  }

  void Stage::checkOutOfBounds(Entities::Entity* pEntity) {
    if (pEntity->getEntityType() == Entities::EntityType::Static)
      return;

    sf::Vector2f pos = pEntity->getPosition();
    sf::Vector2f size = m_pGraphicsManager->getStageSize();

    if (pos.x < 0.f || pos.x > size.x || pos.y < 0.f || pos.y > size.y)
      pEntity->outOfBounds();
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
      applyPhysics(*it);
      checkOutOfBounds(*it);
      (*it)->exec();
      ++it;
    }
  }

  void Stage::updateView() {
    List<Entities::Entity*>::Iterator it;
    int i;

    for (it = m_players.first(), i = 0; it != m_players.last(); ++it, ++i)
      m_pGraphicsManager->updateView(m_views[i], (*it)->getPosition().x, (*it)->getPosition().y);
  }

  void Stage::verifyGameOver() {
    bool gameOver = true;
    List<Entities::Entity*>::Iterator it;
    
    for (it = m_players.first(); it != m_players.last(); ++it) {
      Entities::Characters::Player* player = static_cast<Entities::Characters::Player*>(*it);
      if (player->getHealthPoints() > 0)
        gameOver = false;
    }

    if (gameOver)
      m_pGameState->gameOver();
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

    updateView();
    verifyGameOver();
  }

  void Stage::draw() {
    for (int i = 0; i < static_cast<int>(m_views.size()); ++i) {
      m_pGraphicsManager->setView(m_views[i]);
      drawEntities(m_staticEntities);
      drawEntities(m_dynamicEntities);
      drawEntities(m_players);
    }
  }

  void Stage::setPaused(const bool paused) {
    m_paused = paused;
  }

  void Stage::exec() {
    if (!m_paused)
      update();
    deleteEntitiesInQueue();
    draw();
  }
}
