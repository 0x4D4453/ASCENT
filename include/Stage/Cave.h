#ifndef FIRSTSTAGE_H
#define FIRSTSTAGE_H

/* Program Defined */
#include "Stage/Stage.h"
#include "Entities/Characters/Fly.h"

/* Forward Declaration */
namespace States { class GameState; }

namespace Stages {
  class Cave : public Stage {
    private:
      Entities::Characters::Fly* m_pFly;
      const int m_maxFlyInstances;
      const int m_flyChance;
      int m_flyNumber;

    private:
      virtual void loadTextures();
      virtual void createFly(sf::Vector2f& position);
    
    public:
      Cave(
        ResourceHolder<Textures::ID, sf::Texture>* pTextureHolder,
        Entities::EntityFactory* pEntityFactory,
        States::GameState* pGameState
      );
      ~Cave();

      virtual void createRandomEnemy(sf::Vector2f& position);
      virtual void createRandomObstacle(sf::Vector2f& position);
  };
}

#endif