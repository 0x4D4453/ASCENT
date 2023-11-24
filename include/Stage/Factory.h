#ifndef SECONDSTAGE_H
#define SECONDSTAGE_H

/* Program Defined */
#include "Stage/Stage.h"
#include "Entities/Characters/Tyrant.h"
#include "Entities/Obstacles/Spring.h"

/* Forward Declaration */
namespace States { class GameState; }

namespace Stages {
  class Factory : public Stage {
    private:
      Entities::Characters::Tyrant* m_pTyrant;
      Entities::Obstacles::Spring* m_pSpring;
      const int m_maxTyrantInstances;
      const int m_maxSpringInstances;
      const int m_tyrantChance;
      const int m_springChance;
      int m_tyrantNumber;
      int m_springNumber;

    private:
      virtual void loadTextures();
      virtual void createTyrant(sf::Vector2f& position);
      virtual void createSpring(sf::Vector2f& position);

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