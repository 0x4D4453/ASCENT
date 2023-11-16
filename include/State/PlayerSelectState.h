#ifndef PLAYERSELECTSTATE_H
#define PLAYERSELECTSTATE_H

/* Program Defined */
#include "State/OptionsState.h"

namespace States {
  class PlayerSelectState : public OptionsState {
    private:
      enum Options {
        OnePlayer,
        TwoPlayer,
        TotalOptions
      };

    private:
      Options m_currentOption;
      std::vector<sf::Sprite> m_sprites;
    
    private:
      void setup();
      void movePreviousOption();
      void moveNextOption();
      void changeState();
    
    public:
      PlayerSelectState();
      ~PlayerSelectState();
      virtual void keyPressed(const sf::Keyboard::Key key);
      void exec();
  };
}

#endif