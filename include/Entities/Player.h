#ifndef PLAYER_H
#define PLAYER_H

/* Program Defined */
#include "Entities/Character.h"

namespace Entities {
  class Player : public Character {
    private:
      int m_points;
      bool m_isJumping;
      bool m_isCharging;
      float m_jumpHeight;
      const float m_chargingSpeed;
      const float m_minJumpHeight;
      const float m_maxJumpHeight;

    private:
      void setup();
      void handleInput();
      void update();
    
    public:
      Player();
      ~Player();
      void setIsJumping(const bool isJumping);
      void chargeJump();
      void jump();
      void exec();
      void save();
  };
}

#endif 