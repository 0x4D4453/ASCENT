#ifndef PLAYER_H
#define PLAYER_H

/* Program Defined */
#include "Entities/Character.h"

namespace Entities {
  class Player : public Character {
    private:
      int m_points;
      bool m_isJumping;
      const float m_jumpHeight;

    private:
      void setup();
      void handleInput();
      void update();
      
    public:
      Player();
      ~Player();
      void setIsJumping(const bool isJumping);
      void exec();
      void save();
  };
}

#endif 