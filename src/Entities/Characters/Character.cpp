/* Main Include */
#include "Entities/Characters/Character.h"

/* Program Defined */
#include "Utility/CustomVector.h"
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
    }

    Character::~Character() {
      if (m_animation)
        delete m_animation;

      m_animation = NULL;
    }

    void Character::handleDamage(const int damage) {
      m_sprite.setColor(sf::Color::Red);
    }

    void Character::neutralized() {
      m_sprite.setColor(sf::Color::White);
      m_collisionStrategies.clear();
      m_isKnockbackResistant = true;

      if (m_animation)
        m_animation->update(m_dt);
    }

    void Character::recoverColor() {
      sf::Color color = m_sprite.getColor();

      if (color.r < 255)
        color += sf::Color(750.f * m_dt, 0, 0);

      if (color.g < 255)
        color += sf::Color(0, 750.f * m_dt, 0);

      if (color.b < 255)
        color += sf::Color(0, 0, 750.f * m_dt);

      if (color.a < 255)
        color += sf::Color(0, 0, 0, 750.f * m_dt);

      m_sprite.setColor(color);
    }

    void Character::setAnimation(Animations::Animation* animation) {
      if (!animation)
        return;
        
      if (m_animation)
        delete m_animation;

      m_animation = animation;
    }

    bool Character::checkGrounded(Entity *pEntity, Manager::Collision::CollisionType type) {
      if (type == Manager::Collision::CollisionType::Vertical && getPosition().y <= pEntity->getPosition().y && m_isMidAir) {
        m_isMidAir = false;
        setIsStaggered(false);
        return true;
      }

      return false;
    }

    const int Character::getMaxHealthPoints() const {
      return m_maxHealthPoints;
    }

    const int Character::getHealthPoints() const {
      return m_healthPoints;
    }

    void Character::setHealthPoints(const int healthPoints) {
      if (healthPoints < m_healthPoints)
        handleDamage(m_healthPoints - healthPoints);
      
      m_healthPoints = healthPoints;

      if (m_healthPoints <= 0.f)
        neutralized();
    }

    const bool Character::getIsMidAir() const {
      return m_isMidAir;
    }

    void Character::setIsMidAir(const bool isMidAir) {
      m_isMidAir = isMidAir;
    }

    const float Character::getCurrentSpeed() const {
      CustomVector speedVector(m_velocity);
      return speedVector.getMagnitude();
    }

    void Character::outOfBounds() {
      setHealthPoints(0);
    }

    void Character::save(nlohmann::ordered_json& jsonData) {
      Entity::save(jsonData);
      jsonData["hp"] = m_healthPoints;
      jsonData["isMidAir"] = m_isMidAir;
    }

    void Character::loadSave(const nlohmann::ordered_json& jsonData) {
      Entity::loadSave(jsonData);
      m_healthPoints = jsonData["hp"].template get<int>();
      m_isMidAir = jsonData["isMidAir"].template get<bool>();
      if (m_healthPoints <= 0)
        neutralized();
    }

    void Character::exec() {
      if (m_healthPoints > 0) {
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

        if (m_isStaggered && getCurrentSpeed() < 0.5f)
          m_isStaggered = false;
      }

      move();
    }
  }
}