#ifndef PLAYER_H
#define PLAYER_H

/* Program Defined */
#include "Animation/PlayerAnimation.h"
#include "Entities/Character.h"

/* Standard Library */
#include <map>
#include <unordered_map>

/* SFML Library */
#include <SFML/Audio.hpp>

/* Forward Declaration */
namespace Entities { class Enemy; }

namespace Entities {
  class Player : public Character {
    public:
      enum Actions {
        None,
        MoveLeft,
        MoveRight,
        Jump
      };

    private:
      Animations::PlayerAnimation m_animation;
      std::map<sf::Keyboard::Key, Actions> m_keyBinding;
      int m_points;
      bool m_isJumping;
      bool m_isCharging;
      float m_jumpHeight;
      const float m_chargingSpeed;
      const float m_minJumpHeight;
      const float m_maxJumpHeight;
      const float m_attackSpeed;
      sf::Sound m_jumpSound;

    private:
      void setup();
      void update();
      const float getCurrentSpeed() const;
      void attack(Enemy *enemy);
    
    public:
      Player(
              sf::Texture& playerTexture
            , sf::SoundBuffer& jumpSoundBuffer
            , sf::Keyboard::Key moveLeftKey = sf::Keyboard::A
            , sf::Keyboard::Key moveRightKey = sf::Keyboard::D
            , sf::Keyboard::Key jumpKey = sf::Keyboard::W);
      ~Player();

      const bool getIsJumping() const;
      void setIsJumping(const bool isJumping);
      const bool getIsCharging() const;
      void setIsCharging(const bool isCharging);
      const bool isAttacking();
      Actions getKeyAction(sf::Keyboard::Key key);

      void moveLeft();
      void moveRight();
      void chargeJump();
      void jump();

      virtual void collide(Entity *entity, Manager::Collision::CollisionType type, float overlap);
      virtual void exec();
      virtual void save();
  };
}

#endif 