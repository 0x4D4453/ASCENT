#ifndef FOURTHSTAGE_H
#define FOURTHSTAGE_H

/* Program Defined */
#include "Stage/Stage.h"

namespace Stages {
  class FourthStage : public Stage {
    private:
      virtual void setup();
    
    public:
      FourthStage(const std::string& mapTxt = Constants::STAGE_4);
      ~FourthStage();
  };
}

#endif