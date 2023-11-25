/* Main Include */
#include "Entities/Obstacles/Coin.h"

/* Program Defined */
#include "Stage/Stage.h"

namespace Entities {
  namespace Obstacles {
    Coin::Coin(Textures::ID textureID, sf::Texture& texture, sf::Vector2f position, sf::SoundBuffer& soundBuffer, Stages::Stage* pStage)
      : Obstacle(position, false)
      , m_value(1)
      , m_coinSound(soundBuffer)
      , m_pStage(pStage)
      , m_visible(true)
    {
      setEntityId(EntityID::CoinE);
      setTextureID(textureID);
      setTexture(texture);

      setCollisionStrategy(EntityTag::PlayerTag, Manager::Collision::StrategyId::PhaseCollision);
      setCollisionStrategy(EntityTag::EnemyTag, Manager::Collision::StrategyId::PhaseCollision);
    }

    Coin::~Coin() {

    }

    void Coin::reactToCollision(Entity *pEntity, Manager::Collision::CollisionType type, float overlap) {
      switch (pEntity->getEntityTag()) {
        case EntityTag::PlayerTag:
          if (m_visible) {
            m_coinSound.play();
            static_cast<Characters::Player*>(pEntity)->operator+(m_value);
            m_sprite.setColor(sf::Color::Transparent);
            m_visible = false;
          }
          break;
        default:
          break;
      }
    }

    void Coin::save(nlohmann::ordered_json& jsonData) {
      Obstacle::save(jsonData);
      jsonData["visible"] = m_visible;
    }

    void Coin::loadSave(const nlohmann::ordered_json& jsonData) {
      Obstacle::loadSave(jsonData);
      m_visible = jsonData["visible"].template get<bool>();
      if (!m_visible)
        m_sprite.setColor(sf::Color::Transparent);
    }

    void Coin::exec() {

    }
  }
}