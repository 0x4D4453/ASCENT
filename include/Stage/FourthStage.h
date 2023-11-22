#ifndef FOURTHSTAGE_H
#define FOURTHSTAGE_H

/* Program Defined */
#include "Stage/Stage.h"

/* Forward Declaration */
namespace States { class GameState; }

namespace Stages {
  class FourthStage : public Stage {
    private:
      virtual void setup();
    
    public:
      FourthStage(States::GameState* pGameState, const std::string& mapTxt = Constants::STAGE_4);
      ~FourthStage();
  };
}

#endif