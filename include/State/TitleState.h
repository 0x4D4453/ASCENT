#ifndef TITLESTATE_H
#define TITLESTATE_H

/* Program Defined */
#include "State/State.h" 

namespace States {
  class TitleState : public State {
    private:
      sf::Text m_title;
      sf::Text m_pressStart;
      bool m_startVisible;
      float m_maxEffectTime;
    
    public:
      TitleState();
      ~TitleState();
      virtual void keyPressed(const sf::Keyboard::Key key);
      void update();
      void exec();
  };
}

#endif