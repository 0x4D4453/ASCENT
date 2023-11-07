#ifndef PLAYER_H
#define PLAYER_H

/* Program Defined */
#include "Entities/Character.h"

/* Standard Library */
#include <map>
#include <unordered_map>

namespace Entities {
  class Player : public Character {
    private:
      enum Actions {
        MoveLeft,
        MoveRight,
        Jump
      };

    private:
      std::map<sf::Keyboard::Key, Actions> m_keyBinding;
      std::unordered_map<Actions, void(Player::*)()> m_actionBinding;
      int m_points;
      bool m_isJumping;
      bool m_isCharging;
      float m_jumpHeight;
      const float m_chargingSpeed;
      const float m_minJumpHeight;
      const float m_maxJumpHeight;

    private:
      void setup(const char* texturePath);
      void moveLeft();
      void moveRight();
      void chargeJump();
      void jump();
      void handleInput();
      void update();
    
    public:
      Player(const char* texturePath
            , sf::Keyboard::Key moveLeftKey = sf::Keyboard::A
            , sf::Keyboard::Key moveRightKey = sf::Keyboard::D
            , sf::Keyboard::Key jumpKey = sf::Keyboard::W);
      ~Player();
      void exec();
      void setIsJumping(const bool isJumping);
      void save();
  };
}

#endif 