/* Main Include */
#include "Entities/Characters/Player.h"

/* Program Defined */
#include "Animation/PlayerAnimation.h"
#include "Entities/Characters/Enemy.h"
#include "Utility/Constants.h"

/* Standard Library */
#include <cmath>
#include <fstream>
#include <map>
#include <unordered_map>

/* SFML Library */
#include <SFML/Audio.hpp>

/* JSON Library */
#include "nlohmann/json.hpp"

namespace Entities {
  namespace Characters {
    Player::Player(sf::Texture& playerTexture, sf::SoundBuffer& jumpSoundBuffer, sf::Keyboard::Key moveLeftKey, sf::Keyboard::Key moveRightKey, sf::Keyboard::Key jumpKey)
      : Character(Constants::SCALE, 10.f)
      , m_points(0)
      , m_isAttacking(false)
      , m_isCharging(false)
      , m_chargingSpeed(10.f)
      , m_jumpHeight(2.f)
      , m_minJumpHeight(2.f)
      , m_maxJumpHeight(12.5f)
      , m_attackSpeed(3.5f)
      , m_maxWalkingSpeed(2.5f)
    {
      setEntityId(EntityID::PlayerE);
      setEntityTag(EntityTag::PlayerTag);

      m_keyBinding.insert(std::make_pair(MoveLeft, moveLeftKey));
      m_keyBinding.insert(std::make_pair(MoveRight, moveRightKey));
      m_keyBinding.insert(std::make_pair(Jump, jumpKey));

      m_actionBinding.insert(std::make_pair(MoveLeft, &Player::moveLeft));
      m_actionBinding.insert(std::make_pair(MoveRight, &Player::moveRight));
      m_actionBinding.insert(std::make_pair(Jump, &Player::chargeJump));
      
      setTexture(playerTexture);
      m_jumpSound.setBuffer(jumpSoundBuffer);

      setAnimation(new Animations::PlayerAnimation(this));
    }

    Player::~Player() {
      m_keyBinding.clear();
      m_actionBinding.clear();
    }

    void Player::moveLeft() {
      m_velocity.x -= m_speed * m_dt;

      if (m_velocity.x < -m_maxWalkingSpeed)
        m_velocity.x = -m_maxWalkingSpeed;
    }

    void Player::moveRight() {
      m_velocity.x += m_speed * m_dt;

      if (m_velocity.x > m_maxWalkingSpeed)
        m_velocity.x = m_maxWalkingSpeed;
    }

    const bool Player::getIsCharging() const {
      return m_isCharging;
    }

    void Player::setIsCharging(const bool isCharging) {
      m_isCharging = isCharging;
    }

    const bool Player::getIsAttacking() {
      return m_isAttacking;
    }

    void Player::checkIsAttacking() {
      const float speed = getCurrentSpeed();
      bool isAttacking = speed > m_attackSpeed;

      if (isAttacking)
        setCollisionStrategy(EntityTag::EnemyTag, Manager::Collision::StrategyId::KnockbackCollision);
      else
        setCollisionStrategy(EntityTag::EnemyTag, Manager::Collision::StrategyId::PhaseCollision);

      m_isAttacking = isAttacking;
    }

    void Player::handleInput() {
      // m_velocity.x = 0.f;
      
      using sf::Keyboard;
      std::map<Actions, Keyboard::Key>::iterator it = m_keyBinding.begin();

      while (it != m_keyBinding.end()) {
        if (Keyboard::isKeyPressed((*it).second)) {
          Actions action = (*it).first;
          using functionPointer = void (Player::*)();
          functionPointer pFunction = m_actionBinding[action];
          (this->*pFunction)();
        }
        ++it;
      }

      if (!Keyboard::isKeyPressed(m_keyBinding[Jump]) && m_isCharging)
        jump();
    }

    void Player::chargeJump() {
      if (m_isMidAir)
        return;

      m_isCharging = true;
      m_jumpHeight += m_chargingSpeed * m_dt;

      if (m_jumpHeight > m_maxJumpHeight)
        m_jumpHeight = m_maxJumpHeight;

      m_velocity.x = 0;
    }

    void Player::jump() {
      m_jumpSound.play();

      if (sf::Keyboard::isKeyPressed(m_keyBinding[MoveLeft]))
        m_velocity.x = -m_speed * 1.5f * m_dt;
      else if (sf::Keyboard::isKeyPressed(m_keyBinding[MoveRight]))
        m_velocity.x = m_speed * 1.5f * m_dt;

      m_isCharging = false;
      m_isMidAir = true;
      m_velocity.y = -m_jumpHeight;

      m_jumpHeight = m_minJumpHeight;
    }

    void Player::update() {
      if (!m_isMidAir && !m_isStaggered)
        handleInput();

      if (m_isMidAir)
        checkIsAttacking();
      else
        m_isAttacking = false;
    }

    void Player::reactToCollision(Entity *pEntity, Manager::Collision::CollisionType type, float overlap) {
      if (checkGrounded(pEntity, type))
        m_isAttacking = false;
        
      switch (pEntity->getEntityTag()) {
        case EntityTag::EnemyTag:
          if (getIsAttacking())
            attack(dynamic_cast<Enemy*>(pEntity));
          break;
        default:
          break;
      }
    }

    void Player::attack(Enemy* pEnemy) {
      pEnemy->setHealthPoints(pEnemy->getHealthPoints() - 1);
      pEnemy->setIsStaggered(true);
    }

    void Player::save(nlohmann::ordered_json& jsonData) {
      nlohmann::ordered_json playerData;

      playerData["hp"] = getHealthPoints();
      playerData["score"] = m_points;
      playerData["position"] = { {"x", getPosition().x}, {"y", getPosition().y} };
      playerData["velocity"] = { {"x", getVelocity().x}, {"y", getVelocity().y} };
      playerData["isCharging"] = m_isCharging;
      playerData["isStaggered"] = m_isStaggered;

      jsonData.push_back(playerData);
    }

    void Player::loadSave(const nlohmann::ordered_json& jsonData) {
      setPosition(sf::Vector2f(jsonData["position"]["x"].template get<float>(), jsonData["position"]["y"].template get<float>()));
      setVelocity(sf::Vector2f(jsonData["velocity"]["x"].template get<float>(), jsonData["velocity"]["y"].template get<float>()));
      m_isCharging = jsonData["isCharging"].template get<bool>();
      m_isStaggered = jsonData["isStaggered"].template get<bool>();
    }
  }
}