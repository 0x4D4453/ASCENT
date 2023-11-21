/* Main Include */
#include "Entities/Characters/Tyrant.h"

/* Program Defined */
#include "Entities/Characters/TyrantStates/TyrantIdleState.h"
#include "Entities/Characters/TyrantStates/TyrantFollowingState.h"
#include "Entities/Characters/TyrantStates/TyrantShootingState.h"
#include "Entities/Characters/Player.h"
#include "Animation/TyrantAnimation.h"
#include "Stage/Stage.h"
#include "Utility/Constants.h"

/* Standard Library */
#include <stdlib.h>

namespace Entities {
  namespace Characters {
    Tyrant::Tyrant(Textures::ID textureID, sf::Texture& texture, const sf::Vector2f spawnPosition, Stages::Stage* pStage)
      : Enemy(spawnPosition, Constants::SCALE * 15.f, 15)
      , m_pStage(pStage)
      , m_pState(new TyrantFollowingState(this, pStage))
      , m_isCharging(false)
      , m_isLanding(false)
      , m_isShooting(false)
    {
      setEntityId(EntityID::TyrantE);
      setTextureID(textureID);
      setTexture(texture);
      setSpeed(25.f);
      setKnockback(5.f);

      setAnimation(new Animations::TyrantAnimation(this, 0.5f));
      m_sprite.setHitbox({ 4.f, 5.f, 8.f, 11.f });

      m_isKnockbackResistant = true;
    }

    Tyrant::~Tyrant() {
      delete m_pState;
      m_pStage = NULL;
      m_pState = NULL;
    }

    void Tyrant::changeState(TyrantStateID id) {
      TyrantState* pState;

      switch (id) {
        case TyrantStateID::Idle:
          pState = new TyrantIdleState(this, m_pStage);
          break;
        case TyrantStateID::Following:
          pState = new TyrantFollowingState(this, m_pStage);
          break;
        case TyrantStateID::Shooting:
          pState = new TyrantShootingState(this, m_pStage);
          break;
        default:
          pState = new TyrantIdleState(this, m_pStage);
          break;
      }

      if (!pState)
        pState = new TyrantIdleState(this, m_pStage);

      delete m_pState;
      m_pState = pState;
    }

    const bool Tyrant::getIsCharging() const {
      return m_isCharging;
    }

    void Tyrant::setIsCharging(const bool is) {
      m_isCharging = is;
    }

    const bool Tyrant::getIsLanding() const {
      return m_isLanding;
    }

    void Tyrant::setIsLanding(const bool is) {
      m_isLanding = is;
    }

    const bool Tyrant::getIsShooting() const {
      return m_isShooting;
    }

    void Tyrant::setIsShooting(const bool is) {
      m_isShooting = is;
    }

    const int Tyrant::getCurrentFrame() const {
      return m_animation->getCurrentFrame();
    }

    void Tyrant::movementPattern() {
      m_pState->movementPattern();
    }

    void Tyrant::collide(Entity *pEntity, Manager::Collision::CollisionType type, float overlap) {
      if (m_healthPoints <= 0)
        return;

      switch (pEntity->getEntityTag()) {
        case EntityTag::PlayerTag:
          playerCollide(dynamic_cast<Player*>(pEntity), type);
          break;
        default:
          checkGrounded(pEntity, type);
          break;
      }
    }

    void Tyrant::playerCollide(Characters::Player* pPlayer, Manager::Collision::CollisionType type) {
      if (pPlayer->getIsAttacking()) {        
        if (type == Manager::Collision::CollisionType::Horizontal && pPlayer->getIsMidAir()) {
          setCollisionStrategy(EntityTag::PlayerTag, Manager::Collision::StrategyId::Default);
          pPlayer->setVelocity(sf::Vector2f(-pPlayer->getVelocity().x, pPlayer->getVelocity().y));
          pPlayer->setIsStaggered(true);
        } else {
          setCollisionStrategy(EntityTag::PlayerTag, Manager::Collision::StrategyId::KnockbackCollision);
        }
      } else {
        if (m_collisionClock.restart().asSeconds() < getCollisionStrategy(EntityTag::PlayerTag)->getDelay())
          return;

        setCollisionStrategy(EntityTag::PlayerTag, Manager::Collision::StrategyId::KnockbackCollision);
        damagePlayer(pPlayer);
      }
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
      if (!m_isStaggered && m_healthPoints > 0) {
        movementPattern();
        m_pState->update(m_dt);
      }
    }
  }
}