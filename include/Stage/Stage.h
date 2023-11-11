#ifndef STAGE_H
#define STAGE_H

/* Program Defined */
#include "Entities/Entity.h"
#include "Entities/EntityList.h"
#include "Entities/Player.h"
#include "Manager/CollisionManager.h"

/* Forward Declaration */
namespace Manager { class GraphicsManager; }

namespace Stages {
  class Stage {
    protected:
      static Manager::GraphicsManager* m_graphicsManager;
      Manager::CollisionManager m_collisionManager;
      EntityList m_players;
      EntityList m_platforms;
      EntityList m_enemies;
      bool m_paused;

    protected:
      void createPlatform(const sf::Vector2f position, const char* texture);
      void createEnemy(const sf::Vector2f position, const char* texture);
      void createMap();
      void drawEntities(EntityList& entityList);
      void updateEntities(EntityList& entityList);
      void update();
      void setPlayerPosition(int height);
    
    public:
      Stage(const bool newGame = true);
      ~Stage();
      void setPaused(const bool paused);
      void loadSaveGame();
      void saveGame();
      virtual void exec();
  };
}

#endif