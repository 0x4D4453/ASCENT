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
    , m_jumpHeight(0.3f)
  {
    setup();
  }

  Player::~Player() {

  }

  void Player::setup() {  
    setTexture(Constants::PLAYER_TEXTURE);
    m_sprite.setScale(sf::Vector2f(2.f, 2.f));
    m_sprite.setOrigin(16/2, 0);
    m_sprite.setPosition(sf::Vector2f(32.f,  0.f));
  } 

  void Player::setIsJumping(const bool isJumping) {
    m_isJumping = isJumping;
  }

  void Player::handleInput() {
    m_velocity.x = 0.f;
    m_velocity.y += Constants::GRAVITY * m_dt;

    using sf::Keyboard;
    
    if (Keyboard::isKeyPressed(Keyboard::A))
      m_velocity.x -= m_speed * m_dt;
    if (Keyboard::isKeyPressed(Keyboard::D))
      m_velocity.x += m_speed * m_dt;

    if (Keyboard::isKeyPressed(Keyboard::Space) && !m_isJumping) {
      m_velocity.y  = -sqrt(2.0f * Constants::GRAVITY * m_jumpHeight);
      m_isJumping = true;
    }
  }

  void Player::update() {
    if (m_velocity.x < 0)
      m_sprite.setScale(-2.f, 2.f);
    else if (m_velocity.x > 0)
      m_sprite.setScale(2.f, 2.f);
  
    move();
  }

  void Player::exec() {
    handleInput();
    update();
  }

  void Player::save() {

  }
}