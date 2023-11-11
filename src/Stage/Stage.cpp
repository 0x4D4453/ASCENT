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
#include "Utility/ResourceHolder.h"
#include "Utility/Textures.h"

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
    , m_textureHolder()
    , m_soundHolder()
    , m_platforms()
    , m_enemies()
    , m_paused(false)
  {
    Entities::Entity::setCollisionManager(&m_collisionManager);
    loadTextures();
    loadSounds();

    if (!newGame)
      loadSaveGame();

    m_players.include(new Entities::Player(m_textureHolder.getResource(Textures::Player1), m_textureHolder.getResource(Textures::Player1Walk1), m_textureHolder.getResource(Textures::Player1Walk2), m_textureHolder.getResource(Textures::Player1Walk3), m_textureHolder.getResource(Textures::Player1Jump), m_soundHolder.getResource(Sounds::playerJump)));
    m_players.include(new Entities::Player(m_textureHolder.getResource(Textures::Player2), m_textureHolder.getResource(Textures::Player2Walk1), m_textureHolder.getResource(Textures::Player2Walk2), m_textureHolder.getResource(Textures::Player2Walk3), m_textureHolder.getResource(Textures::Player2Jump), m_soundHolder.getResource(Sounds::playerJump), sf::Keyboard::Left, sf::Keyboard::Right, sf::Keyboard::Up));

    m_collisionManager.setPlayersList(&m_players);
    m_collisionManager.setObstaclesList(&m_platforms);
    m_collisionManager.setEnemiesList(&m_enemies);
    
    createMap();
  }

  Stage::~Stage() {

  }

  void Stage::loadTextures() {
    m_textureHolder.load(Textures::Player1, Textures::PLAYER1);
    m_textureHolder.load(Textures::Player1Walk1, Textures::PLAYER1_WALK1);
    m_textureHolder.load(Textures::Player1Walk2, Textures::PLAYER1_WALK2);
    m_textureHolder.load(Textures::Player1Walk3, Textures::PLAYER1_WALK3);
    m_textureHolder.load(Textures::Player1Jump, Textures::PLAYER1_JUMP);

    m_textureHolder.load(Textures::Player2, Textures::PLAYER2);
    m_textureHolder.load(Textures::Player2Walk1, Textures::PLAYER2_WALK1);
    m_textureHolder.load(Textures::Player2Walk2, Textures::PLAYER2_WALK2);
    m_textureHolder.load(Textures::Player2Walk3, Textures::PLAYER2_WALK3);
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

  void Stage::loadSounds() {
    m_soundHolder.load(Sounds::playerJump, Sounds::PLAYER_JUMP);
  }

  void Stage::loadSaveGame() {

  }

  void Stage::saveGame() {

  }

  void Stage::createPlatform(const sf::Vector2f position, Textures::ID textureID) {
    using namespace Entities;
    Entities::Entity* pEntity = NULL;

    pEntity = static_cast<Entity*>(new Platform(m_textureHolder.getResource(textureID), position));

    if (!pEntity) {
      std::cerr << "Error creating platform!\n";
      return;
    }

    m_platforms.include(pEntity);
  }

  void Stage::createEnemy(const sf::Vector2f position, Textures::ID textureID) {
    using namespace Entities;
    Entities::Entity* pEntity = NULL;

    pEntity = static_cast<Entity*>(new Goomba(m_textureHolder.getResource(textureID), position));

    if (!pEntity) {
      std::cerr << "Error creating enemy!\n";
      return;
    }

    m_enemies.include(pEntity);
  }

  void Stage::createMap() {
    std::ifstream stageTxt("assets/stage_2.txt");

    if (!stageTxt) {
      std::cout << "Error loading stage\n";
      exit(24);
    }
      
    int i, j;
    std::string line;
    sf::Vector2f position = sf::Vector2f();

    for (i = 0; std::getline(stageTxt, line); ++i) {
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

    stageTxt.close();

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
