#ifndef THIRDSTAGE_H
#define THIRDSTAGE_H

/* Program Defined */
#include "Stage/Stage.h"

namespace Stages {
  class ThirdStage : public Stage {
    private:
      virtual void setup();
    
    public:
      ThirdStage(const std::string& mapTxt = Constants::STAGE_3);
      ~ThirdStage();
  };
}

#endif