/* Main Include */
#include "Entities/Obstacles/Flag.h"

/* Program Defined */
#include "Stage/Stage.h"

namespace Entities {
  namespace Obstacles {
    Flag::Flag(Textures::ID textureID, sf::Texture& texture, sf::Vector2f position, Stages::Stage* pStage)
      : Obstacle(position, false)
      , m_reached(false)
      , m_pStage(pStage)
    {
      setEntityId(EntityID::FlagE);
      setTextureID(textureID);
      setTexture(texture);

      setCollisionStrategy(EntityTag::PlayerTag, Manager::Collision::StrategyId::PhaseCollision);
      setCollisionStrategy(EntityTag::EnemyTag, Manager::Collision::StrategyId::PhaseCollision);
    }

    Flag::~Flag() {

    }

    void Flag::run() {
      lock();
      m_pStage->saveGame();
      unlock();
      exitThread();
    }

    void Flag::quickSave() {
      if (m_reached)
        return;

      m_reached = true;
      m_sprite.setColor(sf::Color::Green);
      start();
    }

    void Flag::reactToCollision(Entity *pEntity, Manager::Collision::CollisionType type, float overlap) {
      switch (pEntity->getEntityTag()) {
        case EntityTag::PlayerTag:
          quickSave();
          break;
        default:
          break;
      }
    }

    void Flag::save(nlohmann::ordered_json& jsonData) {
      Obstacle::save(jsonData);
      jsonData["reached"] = m_reached;
    }

    void Flag::loadSave(const nlohmann::ordered_json& jsonData) {
      Obstacle::loadSave(jsonData);
      m_reached = jsonData["reached"].template get<bool>();
      if (m_reached)
        m_sprite.setColor(sf::Color::Green);
    }

    void Flag::exec() {

    }
  }
}