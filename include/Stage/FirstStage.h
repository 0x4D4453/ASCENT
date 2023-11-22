#ifndef FIRSTSTAGE_H
#define FIRSTSTAGE_H

/* Program Defined */
#include "Stage/Stage.h"

/* Forward Declaration */
namespace States { class GameState; }

namespace Stages {
  class FirstStage : public Stage {
    private:
      virtual void setup();
    
    public:
      FirstStage(States::GameState* pGameState, const std::string& mapTxt = Constants::STAGE_1);
      ~FirstStage();
  };
}

#endif