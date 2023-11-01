/* Main Include */
#include "Entities/Player.h"

/* Program Defined */
#include "Utility/Constants.h"

/* Standard Library */
#include <cmath>

namespace Entities {
  Player::Player()
    : Character()
    , m_points(0)
    , m_isJumping(false)
    , m_chargingSpeed(0.25f)
    , m_minJumpHeight(0.1f)
    , m_maxJumpHeight(0.8f)
    , m_jumpHeight(m_minJumpHeight)
  {
    setup();
  }

  Player::~Player() {

  }

  void Player::setup() {  
    setTexture(Constants::PLAYER_TEXTURE);
    m_sprite.setScale(sf::Vector2f(Constants::SCALE, Constants::SCALE));
    m_sprite.setOrigin(16/2, 0);
    m_sprite.setPosition(sf::Vector2f(32.f,  0.f));
  } 

  void Player::setIsJumping(const bool isJumping) {
    m_isJumping = isJumping;
  }

  void Player::handleInput() {
    m_velocity.x = 0.f;
    m_velocity.y += Constants::GRAVITY * m_dt;

    if (m_velocity.y > Constants::MAX_FALL_SPEED)
      m_velocity.y = Constants::MAX_FALL_SPEED;

    using sf::Keyboard;
    
    if (Keyboard::isKeyPressed(Keyboard::A))
      m_velocity.x -= m_speed * m_dt;
    if (Keyboard::isKeyPressed(Keyboard::D))
      m_velocity.x += m_speed * m_dt;

    if (Keyboard::isKeyPressed(Keyboard::Space) && !m_isJumping)
      chargeJump();

    if (!Keyboard::isKeyPressed(Keyboard::Space) && m_isCharging)
      jump();
  }

  void Player::chargeJump() {
    m_isCharging = true;
    m_jumpHeight += m_chargingSpeed * m_dt;

    if (m_jumpHeight > m_maxJumpHeight)
      m_jumpHeight = m_maxJumpHeight;
  }

  void Player::jump() {
    m_isCharging = false;
    m_isJumping = true;
    m_velocity.y = -sqrt(2.0f * Constants::GRAVITY * m_jumpHeight);
    m_jumpHeight = m_minJumpHeight;
  }

  void Player::update() {
    if (m_velocity.x < 0)
      m_sprite.setScale(-Constants::SCALE, Constants::SCALE);
    else if (m_velocity.x > 0)
      m_sprite.setScale(Constants::SCALE, Constants::SCALE);
  
    move();
  }

  void Player::exec() {
    handleInput();
    update();
  }

  void Player::save() {

  }
}