/* Main Include */
#include "Stage/FourthStage.h"

/* Program Defined */
#include "State/GameState.h"

namespace Stages {
  FourthStage::FourthStage(States::GameState* pGameState, const std::string& mapTxt) 
    : Stage(pGameState, mapTxt)
  {

  }

  FourthStage::~FourthStage() {

  }

  void FourthStage::createRandomEnemy(sf::Vector2f& position) {
    
  }
}
