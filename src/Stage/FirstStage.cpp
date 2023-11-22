/* Main Include */
#include "Stage/FirstStage.h"

/* Program Defined */
#include "State/GameState.h"

namespace Stages {
  FirstStage::FirstStage(States::GameState* pGameState, const std::string& mapTxt) 
    : Stage(pGameState, mapTxt)
  {

  }

  FirstStage::~FirstStage() {

  }

  void FirstStage::setup() {
    
  }
}
