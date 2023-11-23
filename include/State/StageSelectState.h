#ifndef STAGESELECTSTATE_H
#define STAGESELECTSTATE_H

/* Program Defined */
#include "State/OptionsState.h"

/* Standard Library */
#include <vector>

namespace States {
  class StageSelectState : public OptionsState {
    private:
      enum Options {
        Cave,
        Factory,
        TotalOptions
      };

    private:
      sf::Sprite m_leftArrow;
      sf::Sprite m_rightArrow;
      std::vector<sf::Sprite> m_stageImages;
      sf::RectangleShape m_outlineRect;

    private:
      void setup();
      void changeState();

    public:
      StageSelectState();
      ~StageSelectState();
      virtual void keyPressed(const sf::Keyboard::Key key);
      void exec();
  };
}

#endif