#ifndef STAGESELECTSTATE_H
#define STAGESELECTSTATE_H

/* Program Defined */
#include "State/OptionsState.h"

namespace States {
  class StageSelectState : public OptionsState {
    private:
      enum Options {
        Stage1,
        Stage2,
        TotalOptions
      };

    private:
      Options m_currentOption;

    private:
      void handleEvent(sf::Event& event);
      void setup();
      void movePreviousOption();
      void moveNextOption();
      void changeState();

    public:
      StageSelectState();
      ~StageSelectState();
      void exec();
  };
}

#endif