/* Main Include */
#include "Stage/SecondStage.h"

/* Program Defined */
#include "State/GameState.h"


namespace Stages {
  SecondStage::SecondStage(States::GameState* pGameState, const std::string& mapTxt) 
    : Stage(pGameState, mapTxt)
  {

  }

  SecondStage::~SecondStage() {

  }

  void SecondStage::createRandomEnemy(sf::Vector2f& position) {
    
  }
}
