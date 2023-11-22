#ifndef THIRDSTAGE_H
#define THIRDSTAGE_H

/* Program Defined */
#include "Stage/Stage.h"

/* Forward Declaration */
namespace States { class GameState; }

namespace Stages {
  class ThirdStage : public Stage {
    public:
      ThirdStage(States::GameState* pGameState, const std::string& mapTxt = Constants::STAGE_3);
      ~ThirdStage();
      
      virtual void createRandomEnemy(sf::Vector2f& position);
  };
}

#endif