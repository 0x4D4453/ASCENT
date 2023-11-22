#ifndef SAVESCORESTATE_H
#define SAVESCORESTATE_H

/* Program Defined */
#include "State/OptionsState.h"
#include "UI/TextInput.h"

namespace States {
  class SaveScoreState : public OptionsState {
    private:
      sf::Text m_playerName;
      UI::TextInput m_textInput;

    private:
      void setup();;
      void changeState();
      void saveScore();
    
    public:
      SaveScoreState();
      ~SaveScoreState();
      virtual void keyPressed(const sf::Keyboard::Key key);
      virtual void textEntered(const char text);
      void exec();
  };
}

#endif