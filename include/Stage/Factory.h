#ifndef SECONDSTAGE_H
#define SECONDSTAGE_H

/* Program Defined */
#include "Stage/Stage.h"

/* Forward Declaration */
namespace States { class GameState; }

namespace Stages {
  class Factory : public Stage {
    private:
      virtual void loadTextures();

    public:
      Factory(
        ResourceHolder<Textures::ID, sf::Texture>* pTextureHolder,
        Entities::EntityFactory* pEntityFactory,
        States::GameState* pGameState
      );
      ~Factory();

      virtual void createRandomEnemy(sf::Vector2f& position);
      virtual void createRandomObstacle(sf::Vector2f& position);
  };
}

#endif