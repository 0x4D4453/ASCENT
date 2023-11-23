#ifndef FIRSTSTAGE_H
#define FIRSTSTAGE_H

/* Program Defined */
#include "Stage/Stage.h"
#include "Entities/Characters/Fly.h"
#include "Entities/Characters/Goomba.h"
#include "Entities/Obstacles/Spike.h"

/* Forward Declaration */
namespace States { class GameState; }

namespace Stages {
  class Cave : public Stage {
    private:
      Entities::Characters::Fly* m_pFly;
      Entities::Characters::Goomba* m_pGoomba;
      Entities::Obstacles::Spike* m_pSpike;
      const int m_maxFlyInstances;
      const int m_maxGoombaInstances;
      const int m_maxSpikeInstances;
      const int m_flyChance;
      const int m_goombaChance;
      const int m_spikeChance;
      int m_flyNumber;
      int m_goombaNumber;
      int m_spikeNumber;

    private:
      virtual void loadTextures();
      virtual void createFly(sf::Vector2f& position);
      virtual void createGoomba(sf::Vector2f& position);
      virtual void createSpike(sf::Vector2f& position);
    
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