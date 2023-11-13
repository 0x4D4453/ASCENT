#ifndef FIRSTSTAGE_H
#define FIRSTSTAGE_H

/* Program Defined */
#include "Stage/Stage.h"

namespace Stages {
  class FirstStage : public Stage {
    private:
      virtual void setup();
    
    public:
      FirstStage(const bool newGame = true);
      ~FirstStage();
  };
}

#endif