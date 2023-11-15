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

namespace Entities {
  class Player : public Character {
    private:
      enum Actions {
        MoveLeft,
        MoveRight,
        Jump
      };

    private:
      Animations::PlayerAnimation m_animation;
      std::map<Actions, sf::Keyboard::Key> m_keyBinding;
      std::unordered_map<Actions, void(Player::*)()> m_actionBinding;
      int m_points;
      bool m_isJumping;
      bool m_isCharging;
      float m_jumpHeight;
      const float m_chargingSpeed;
      const float m_minJumpHeight;
      const float m_maxJumpHeight;
      sf::Sound m_jumpSound;

    private:
      void setup();
      void moveLeft();
      void moveRight();
      void chargeJump();
      void jump();
      void handleInput();
      void update();
    
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
      virtual void collide(Entity *entity, Manager::Collision::CollisionType type, float overlap);
      virtual void exec();
      virtual void save();
  };
}

#endif 