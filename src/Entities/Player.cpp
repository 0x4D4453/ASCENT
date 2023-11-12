/* Main Include */
#include "Entities/Player.h"

/* Program Defined */
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
  Player::Player(sf::Texture& playerTexture, sf::SoundBuffer& jumpSoundBuffer, sf::Keyboard::Key moveLeftKey, sf::Keyboard::Key moveRightKey, sf::Keyboard::Key jumpKey)
    : Character()
    , m_animation(this)
    , m_points(0)
    , m_isJumping(false)
    , m_isCharging(false)
    , m_chargingSpeed(10.f)
    , m_minJumpHeight(2.f)
    , m_maxJumpHeight(10.f)
    , m_jumpHeight(m_minJumpHeight)
  {
    setEntityId(EntityID::PlayerE);
    
    m_pCollision = m_pCollisionManager->getCollisionStrategy(Manager::Collision::StrategyId::Player);

    m_keyBinding.insert(std::make_pair(MoveLeft, moveLeftKey));
    m_keyBinding.insert(std::make_pair(MoveRight, moveRightKey));
    m_keyBinding.insert(std::make_pair(Jump, jumpKey));

    m_actionBinding.insert(std::make_pair(MoveLeft, &Player::moveLeft));
    m_actionBinding.insert(std::make_pair(MoveRight, &Player::moveRight));
    m_actionBinding.insert(std::make_pair(Jump, &Player::chargeJump));
    
    setTexture(playerTexture);
    m_jumpSound.setBuffer(jumpSoundBuffer);

    setup();
  }

  Player::~Player() {
    m_keyBinding.clear();
    m_actionBinding.clear();
  }

  void Player::setup() {  
    m_sprite.setOrigin(Constants::SPRITE_SIZE/2.f, 0);
    m_sprite.setPosition(sf::Vector2f(Constants::TILE_SIZE * 15,  0.f));
  }

  void Player::moveLeft() {
    m_velocity.x -= m_speed * m_dt;
  }

  void Player::moveRight() {
    m_velocity.x += m_speed * m_dt;
  }

  const bool Player::getIsJumping() const {
    return m_isJumping;
  }

  void Player::setIsJumping(const bool isJumping) {
    m_isJumping = isJumping;
  }

  const bool Player::getIsCharging() const {
    return m_isCharging;
  }

  void Player::setIsCharging(const bool isCharging) {
    m_isCharging = isCharging;
  }

  void Player::handleInput() {
    m_velocity.x = 0.f;
    
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
    if (m_isJumping)
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
      moveLeft();
    else if (sf::Keyboard::isKeyPressed(m_keyBinding[MoveRight]))
      moveRight();

    m_isCharging = false;
    m_isJumping = true;
    m_velocity.y = -m_jumpHeight;

    m_jumpHeight = m_minJumpHeight;
  }

  void Player::update() {
    m_animation.update(m_dt, m_isJumping, m_isCharging, m_isStaggered, m_velocity);

    if (m_velocity.x < 0)
      m_sprite.setScale(-Constants::SCALE, Constants::SCALE);
    else if (m_velocity.x > 0)
      m_sprite.setScale(Constants::SCALE, Constants::SCALE);

    move();
  }

  void Player::exec() {
    if (!m_isJumping && !m_isStaggered)
      handleInput();

    update();
  }

  void Player::save() {
    nlohmann::json playerData;

    playerData["hp"] = getHealthPoints();
    playerData["position"] = { {"x", getPosition().x}, {"y", getPosition().y} };
    playerData["velocity"] = { {"x", getVelocity().x}, {"y", getVelocity().y} };
 
    std::ofstream jsonOut("saves/player.json");
    jsonOut << std::setw(2) << playerData;
  }
}