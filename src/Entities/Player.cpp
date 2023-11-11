/* Main Include */
#include "Entities/Player.h"

/* Program Defined */
#include "Utility/Constants.h"

/* Standard Library */
#include <cmath>
#include <fstream>
#include <map>
#include <unordered_map>

/* JSON Library */
#include "nlohmann/json.hpp"

namespace Entities {
  Player::Player(const char* idleTexturePath, const char* walk1TexturePath, const char* walk2TexturePath, const char* walk3TexturePath, const char* jumpTexturePath, sf::Keyboard::Key moveLeftKey, sf::Keyboard::Key moveRightKey, sf::Keyboard::Key jumpKey)
    : Character()
    , m_animation(this)
    , m_points(0)
    , m_isJumping(false)
    , m_chargingSpeed(0.25f)
    , m_minJumpHeight(0.1f)
    , m_maxJumpHeight(580.f)
    , m_jumpHeight(m_minJumpHeight)
  {
    m_keyBinding.insert(std::make_pair(moveLeftKey, MoveLeft));
    m_keyBinding.insert(std::make_pair(moveRightKey, MoveRight));
    m_keyBinding.insert(std::make_pair(jumpKey, Jump));

    m_actionBinding.insert(std::make_pair(MoveLeft, &Player::moveLeft));
    m_actionBinding.insert(std::make_pair(MoveRight, &Player::moveRight));
    m_actionBinding.insert(std::make_pair(Jump, &Player::jump));

    /* Resource Holder */
    sf::Texture* pTexture = new sf::Texture();

    pTexture->loadFromFile(idleTexturePath);
    m_animation.includeFrame(pTexture);
    pTexture = new sf::Texture();
    pTexture->loadFromFile(walk1TexturePath);
    m_animation.includeFrame(pTexture);
    pTexture = new sf::Texture();
    pTexture->loadFromFile(walk2TexturePath);
    m_animation.includeFrame(pTexture);
    pTexture = new sf::Texture();
    pTexture->loadFromFile(walk3TexturePath);
    m_animation.includeFrame(pTexture);
    pTexture = new sf::Texture();
    pTexture->loadFromFile(jumpTexturePath);
    m_animation.includeFrame(pTexture);

    setup();
  }

  Player::~Player() {

  }

  void Player::setup() {  
    m_sprite.setOrigin(Constants::SPRITE_SIZE/2.f, 0);
    m_sprite.setPosition(sf::Vector2f(Constants::TILE_SIZE, 0.f));
  } 

  void Player::moveLeft() {
    m_velocity.x -= m_speed * m_dt; 
  }

  void Player::moveRight() {
    m_velocity.x += m_speed * m_dt; 
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
    std::map<Keyboard::Key, Actions>::iterator it = m_keyBinding.begin();

    while (it != m_keyBinding.end()) {
      if (Keyboard::isKeyPressed((*it).first)) {
        Actions action = (*it).second;
        using functionPointer = void (Player::*)();
        functionPointer pFunction = m_actionBinding[action];
        (this->*pFunction)();
      }
      ++it;
    }
  }

  void Player::chargeJump() {
    m_isCharging = true;
    m_jumpHeight += m_chargingSpeed * m_dt;

    if (m_jumpHeight > m_maxJumpHeight)
      m_jumpHeight = m_maxJumpHeight;
  }

  void Player::jump() {
    //m_isCharging = false;
    if (!m_isJumping) {
      m_velocity.y = 0.f;
      m_isJumping = true;
      m_velocity.y -= (m_maxJumpHeight * m_dt);
    }
    //m_jumpHeight = m_minJumpHeight;
  }

  void Player::collide(Entity* entity, CollisionType type, float overlap) {
    if (type == CollisionType::Vertical && overlap < 0)
      setIsJumping(false);
  }

  void Player::update() {
    m_animation.update(m_dt, m_isJumping, m_velocity);

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
    nlohmann::json playerData;

    playerData["hp"] = getHealthPoints();
    playerData["position"] = { {"x", getPosition().x}, {"y", getPosition().y} };
    playerData["velocity"] = { {"x", getVelocity().x}, {"y", getVelocity().y} };
 
    std::ofstream jsonOut("saves/player.json");
    jsonOut << std::setw(2) << playerData;
  }
}