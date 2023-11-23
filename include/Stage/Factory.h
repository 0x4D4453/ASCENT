#ifndef SECONDSTAGE_H
#define SECONDSTAGE_H

/* Program Defined */
#include "Stage/Stage.h"

/* Forward Declaration */
namespace States { class GameState; }

namespace Stages {
  class Factory : public Stage {
    public:
      Factory(States::GameState* pGameState, const std::string& mapTxt = Constants::FACTORY);
      ~Factory();

      virtual void createRandomEnemy(sf::Vector2f& position);
  };
}

#endif