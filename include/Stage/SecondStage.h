#ifndef SECONDSTAGE_H
#define SECONDSTAGE_H

/* Program Defined */
#include "Stage/Stage.h"

namespace Stages {
  class SecondStage : public Stage {
    private:
      virtual void setup();
    
    public:
      SecondStage(const std::string& mapTxt = Constants::STAGE_2);
      ~SecondStage();
  };
}

#endif