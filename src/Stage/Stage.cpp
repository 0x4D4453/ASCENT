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
    , m_dynamicDeletionQueue()
    , m_views()
    , m_viewSeparation(sf::Vector2f(2.f, Constants::WINDOW_HEIGHT))
    , m_players()
    , m_staticEntities()
    , m_dynamicEntities()
    , m_playerHealth()
    , m_pGoomba(NULL)
    , m_maxGoombaInstances(2)
    , m_goombaChance(33)
    , m_goombaNumber(0)
    , m_pSpike(NULL)
    , m_maxSpikeInstances(3)
    , m_spikeChance(25)
    , m_spikeNumber(0)
    , m_paused(false)
  {
    Entities::Entity::setCollisionManager(&m_collisionManager);
    m_pGraphicsManager->resetTime();

    m_collisionManager.setPlayersList(&m_players);
    m_collisionManager.setStaticEntities(&m_staticEntities);
    m_collisionManager.setDynamicEntities(&m_dynamicEntities);

    m_viewSeparation.setPosition(sf::Vector2f(Constants::WINDOW_WIDTH/2.f - 1.f, 0.f));
    m_viewSeparation.setFillColor(sf::Color::White);
  }

  Stage::~Stage() {
    deleteEntitiesInQueue();
    m_pTextureHolder = NULL;
    m_pEntityFactory = NULL;
    m_pGameState = NULL;
    m_pGoomba = NULL;
    m_pSpike = NULL;
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

  void Stage::createGoomba(sf::Vector2f& position) {
    if (m_goombaNumber >= m_maxGoombaInstances)
      return;

    const int random = 1 + rand() % 100;
    if (random < m_goombaChance) {
      sf::Texture& textureRef = m_pEntityFactory->getTexture(Textures::Goomba);
      m_pGoomba = new Entities::Characters::Goomba(Textures::Goomba, textureRef, position);
      m_dynamicEntities.include(static_cast<Entities::Entity*>(m_pGoomba));
    }
  }

  void Stage::createSpike(sf::Vector2f& position) {
    if (m_spikeNumber >= m_maxSpikeInstances)
      return;

    const int random = 1 + rand() % 100;
    if (random < m_spikeChance) {
      sf::Texture& textureRef = m_pEntityFactory->getTexture(Textures::Spikes);
      m_pSpike = new Entities::Obstacles::Spike(Textures::Spikes, textureRef, position);
      m_staticEntities.include(static_cast<Entities::Entity*>(m_pSpike));
    }
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
    nlohmann::ordered_json playersData;
    List<Entities::Entity*>::Iterator playersIterator;

    for (playersIterator = m_players.first(); playersIterator != m_players.last(); ++playersIterator) {
      nlohmann::ordered_json playerData;
      (*playersIterator)->save(playerData);
      playersData.push_back(playerData);
    }
      
    std::ofstream jsonOut("saves/players.json");
    jsonOut << std::setw(2) << playersData;
    jsonOut.close();
  }

  void Stage::saveEntitiesData() {
    nlohmann::ordered_json entitiesData;
    List<Entities::Entity*>::Iterator entitiesIterator;

    for (entitiesIterator = m_staticEntities.first(); entitiesIterator != m_staticEntities.last(); ++entitiesIterator) {
      nlohmann::ordered_json entityData;
      (*entitiesIterator)->save(entityData);
      entitiesData.push_back(entityData);
    }
      
    for (entitiesIterator = m_dynamicEntities.first(); entitiesIterator != m_dynamicEntities.last(); ++entitiesIterator) {
      nlohmann::ordered_json entityData;
      (*entitiesIterator)->save(entityData);
      entitiesData.push_back(entityData);
    }

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

    for (it = m_players.first(), i = 0; it != m_players.last() && i < m_views.size(); ++it, ++i)
      m_pGraphicsManager->updateView(m_views[i], (*it)->getPosition().x, (*it)->getPosition().y);
  }

  const int Stage::getScore() {
    List<Entities::Entity*>::Iterator it;
    int score = 0;

    for (it = m_players.first(); it != m_players.last(); ++it)
      score += static_cast<Entities::Characters::Player*>((*it))->getPoints();

    return score;
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
      m_playerHealth.update(m_dt);
      (*timeSinceLastUpdate) -= (*timePerFrame);
    }

    updateView();
    verifyGameOver();
  }

  void Stage::draw() {
    int i;
    List<Entities::Entity*>::Iterator it = m_players.first();

    for (i = 0; i < static_cast<int>(m_views.size()) && it != m_players.last(); ++i, ++it) {
      m_pGraphicsManager->setView(m_views[i]);
      drawEntities(m_staticEntities);
      drawEntities(m_dynamicEntities);
      drawEntities(m_players);
      m_playerHealth.draw(static_cast<Entities::Characters::Player*>(*it), m_pGraphicsManager);
    }

    if (i > 1) {
      m_pGraphicsManager->resetView();
      m_pGraphicsManager->draw(m_viewSeparation);
    }
  }

  void Stage::setPaused(const bool paused) {
    m_paused = paused;
    if (paused)
      m_bgMusic.pause();
    else 
      m_bgMusic.play();
  }

  void Stage::exec() {
    if (!m_paused)
      update();
    deleteEntitiesInQueue();
    draw();
  }
}
