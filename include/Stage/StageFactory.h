#ifndef STAGEFACTORY_H
#define STAGEFACTORY_H

/* Main include */
#include "Stage/Stage.h"

/* Program Defined */
#include "Entities/Entity.h"
#include "Entities/EntityList.h"
#include "Entities/Player.h"

namespace Manager { class GraphicsManager; }

namespace Stages {
  class StageFactory {
    protected:
      static Manager::GraphicsManager* m_graphicsManager;
      EntityList* m_players;
      EntityList* m_platforms;
      EntityList* m_enemies;
      bool m_newGame;
    
    protected:
      void createMap(const char* stageTxt);
      void createPlatform(const sf::Vector2f position, const char* texture);
      void createEnemy(const sf::Vector2f position, const char* texture);
      void createPlayers(int stageHeight);
    
    public:
      StageFactory(const bool newGame = true);
      ~StageFactory();

      Stage* createStage(const char* stageTxt);
  };
}

#endif