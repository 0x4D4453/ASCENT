/* Main Include */
#include "Entities/Characters/Tyrant.h"
#include "Entities/Characters/TyrantStates/TyrantIdleState.h"

/* Program Defined */
#include "Utility/Constants.h"

/* Standard Library */
#include <stdlib.h>

namespace Entities {
  namespace Characters {
    Tyrant::Tyrant(Textures::ID textureID, sf::Texture& texture, const sf::Vector2f spawnPosition, EntityList* pPlayers)
      : Enemy(spawnPosition)
      , m_followDistance(128.f)
      , m_pState(new TyrantIdleState(this, pPlayers))
      , m_pPlayers(pPlayers)
      , m_timeSinceAction(0.f)
    {
      setEntityId(EntityID::TyrantE);
      setTextureID(textureID);
      setTexture(texture);
      setSpeed(30.f);
      setKnockback(5.f);

      m_scale = Constants::SCALE * 4.f;
    }

    Tyrant::~Tyrant() {
      delete m_pState;
      m_pState = NULL;
      m_pPlayers = NULL;
    }

    void Tyrant::changeState(TyrantStateID id) {
      TyrantState* pState;

      switch (id) {
        case TyrantStateID::Idle:
          m_pState = new TyrantIdleState(this, m_pPlayers);
          break;
        default:
          m_pState = new TyrantIdleState(this, m_pPlayers);
          break;
      }

      delete m_pState;
      m_pState = pState;
    }

    // void Tyrant::jump() {

    // }

    // void Tyrant::chargeJump() {

    // }

    // void Tyrant::launchProjectiles() {

    // }

    // // Código altamente baseado no código do monitor Giovane
    // void Tyrant::followPlayer(sf::Vector2f playerPosition) {
    //   if (playerPosition.x - m_position.x > 0.f)
    //     m_velocity.x = m_speed;
    //   else 
    //     m_velocity.x = -m_speed;
    // }

    // void Tyrant::movementPattern() {
    //   if (m_pPlayers) {
    //     sf::Vector2f playerPosition = m_pPlayer->getPosition();
    //     if (fabs(playerPosition.x - m_position.x) <= m_followDistance &&
    //         fabs(playerPosition.y - m_position.y) <= m_followDistance)
    //       followPlayer(playerPosition);
    //     else
    //       m_velocity.x = 0.f;
    //   }
    // }

    void Tyrant::movementPattern() {
      m_pState->movementPattern();
    }

    void Tyrant::save(nlohmann::ordered_json& jsonData) {
      nlohmann::ordered_json tyrantData;

      tyrantData["ID"] = getEntityId();
      tyrantData["textureID"] = m_textureID;
      tyrantData["hp"] = getHealthPoints();
      tyrantData["spawnPosition"] = { {"x", m_spawnPosition.x}, {"y", m_spawnPosition.y} };
      tyrantData["position"] = { {"x", getPosition().x}, {"y", getPosition().y} };
      tyrantData["velocity"] = { {"x", getVelocity().x}, {"y", getVelocity().y} };

      jsonData.push_back(tyrantData);
    }

    void Tyrant::loadSave(const nlohmann::ordered_json& jsonData) {
      m_spawnPosition = sf::Vector2f(jsonData["spawnPosition"]["x"].template get<float>(), jsonData["spawnPosition"]["y"].template get<float>());
      setVelocity(sf::Vector2f(jsonData["velocity"]["x"], jsonData["velocity"]["y"]));
      m_healthPoints = jsonData["hp"];
    }

    void Tyrant::update() {
      if (m_healthPoints > 0) {
        movementPattern();
        m_pState->doAction();
      }
    }
  }
}