#ifndef SECONDSTAGE_H
#define SECONDSTAGE_H

/* Program Defined */
#include "Stage/Stage.h"

/* Forward Declaration */
namespace States { class GameState; }

namespace Stages {
  class SecondStage : public Stage {
    private:
      virtual void setup();
    
    public:
      SecondStage(States::GameState* pGameState, const std::string& mapTxt = Constants::STAGE_2);
      ~SecondStage();
  };
}

#endif