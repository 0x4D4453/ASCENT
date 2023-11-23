/* Main Include */
#include "Stage/Factory.h"

/* Program Defined */
#include "State/GameState.h"


namespace Stages {
  Factory::Factory(States::GameState* pGameState, const std::string& mapTxt) 
    : Stage(pGameState, mapTxt)
  {

  }

  Factory::~Factory() {

  }

  void Factory::createRandomEnemy(sf::Vector2f& position) {
    
  }
}
