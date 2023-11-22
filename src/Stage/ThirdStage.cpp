/* Main Include */
#include "Stage/ThirdStage.h"

/* Program Defined */
#include "State/GameState.h"

namespace Stages {
  ThirdStage::ThirdStage(States::GameState* pGameState, const std::string& mapTxt) 
    : Stage(pGameState, mapTxt)
  {

  }

  ThirdStage::~ThirdStage() {

  }

  void ThirdStage::setup() {
    
  }
}
