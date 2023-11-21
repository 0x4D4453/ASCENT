/* Main Include */
#include "Entities/Characters/Character.h"

/* Program Defined */
#include "Utility/Constants.h"

namespace Entities {
  namespace Characters {
    Character::Character(const float scale, const int maxHealth)
      : Entity(sf::Vector2f(0.f, 0.f), scale)
      , m_animation(NULL)
      , m_collisionClock()
      , m_maxHealthPoints(maxHealth)
      , m_healthPoints(maxHealth)
      , m_isMidAir(false)
    {
      setEntityId(EntityID::CharacterE);
      setEntityType(EntityType::Dynamic);
      setup();
    }

    Character::~Character() {
      if (m_animation)
        delete m_animation;

      m_animation = NULL;
    }

    void Character::setup() {  
      m_sprite.setOrigin(Constants::SPRITE_SIZE/2.f, 0);
      m_sprite.setPosition(sf::Vector2f(Constants::TILE_SIZE * 15,  0.f));
    }

    void Character::recoverColor() {
      sf::Color color = m_sprite.getColor();

      if (color.r < 255)
        color += sf::Color(1000.f * m_dt, 0, 0);

      if (color.g < 255)
        color += sf::Color(0, 1000.f * m_dt, 0);

      if (color.b < 255)
        color += sf::Color(0, 0, 1000.f * m_dt);

      m_sprite.setColor(color);
    }

    void Character::setAnimation(Animations::Animation* animation) {
      if (!animation)
        return;
        
      if (m_animation)
        delete m_animation;

      m_animation = animation;
    }

    void Character::checkGrounded(Entity *pEntity, Manager::Collision::CollisionType type) {
      if (type == Manager::Collision::CollisionType::Vertical && getPosition().y <= pEntity->getPosition().y && m_isMidAir) {
        m_isMidAir = false;
        setIsStaggered(false);
      }
    }

    const int Character::getMaxHealthPoints() const {
      return m_maxHealthPoints;
    }

    const int Character::getHealthPoints() const {
      return m_healthPoints;
    }

    void Character::setHealthPoints(const int healthPoints) {
      if (healthPoints < m_healthPoints)
        m_sprite.setColor(sf::Color::Red);

      m_healthPoints = healthPoints;
    }

    const bool Character::getIsMidAir() const {
      return m_isMidAir;
    }

    void Character::setIsMidAir(const bool isMidAir) {
      m_isMidAir = isMidAir;
    }

    void Character::exec() {
      recoverColor();
      update();

      if (!getIsColliding())
        m_isMidAir = true;

      if (m_animation)
        m_animation->update(m_dt);

      if (m_velocity.x < 0)
        m_sprite.setScale(-m_scale, m_scale);
      else if (m_velocity.x > 0)
        m_sprite.setScale(m_scale, m_scale);

      move();
    }
  }
}