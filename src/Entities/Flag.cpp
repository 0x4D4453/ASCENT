/* Main Include */
#include "Entities/Flag.h"

/* Program Defined */
#include "Stage/Stage.h"
#include "Utility/Context.h"

namespace Entities {
  Flag::Flag(Textures::ID textureID, sf::Texture& texture, sf::Vector2f position, sf::SoundBuffer& soundBuffer, Stages::Stage* pStage)
    : Entity(position, Constants::SCALE, 0.f)
    , m_pStage(pStage)
    , m_pContext(m_pContext->getInstance())
    , m_reached(false)
    , m_saveSound(soundBuffer)
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
    m_pStage->saveGame(true);
    unlock();
    exitThread();
  }

  void Flag::quickSave() {
    if (m_reached)
      return;

    m_saveSound.play();
    m_reached = true;
    m_sprite.setColor(sf::Color::Green);
    m_pContext->setQuickSave(true);
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
    Entity::save(jsonData);
    jsonData["reached"] = m_reached;
  }

  void Flag::loadSave(const nlohmann::ordered_json& jsonData) {
    Entity::loadSave(jsonData);
    m_reached = jsonData["reached"].template get<bool>();
    if (m_reached)
      m_sprite.setColor(sf::Color::Green);
  }

  void Flag::exec() {

  }
}