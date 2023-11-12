#ifndef STAGE_H
#define STAGE_H

/* Program Defined */
#include "Entities/Entity.h"
#include "Entities/EntityList.h"
#include "Manager/CollisionManager.h"

/* Forward Declaration */
namespace Manager { class GraphicsManager; }

/* SFML Library */
#include <SFML/Audio.hpp>

namespace Stages {
  class Stage {
    protected:
      static Manager::GraphicsManager* m_graphicsManager;
      static const float m_dt;
      Manager::CollisionManager m_collisionManager;
      EntityList m_players;
      EntityList m_platforms;
      EntityList m_enemies;
      bool m_paused;

    protected:
      void applyPhysics(Entities::Entity* entity);
      void drawEntities(EntityList& entityList);
      void updateEntities(EntityList& entityList);
      void update();
    
    public:
      Stage(const bool newGame = true);
      ~Stage();

      EntityList* getPlayers();
      EntityList* getPlatforms();
      EntityList* getEnemies();

      void setPaused(const bool paused);
      void loadSaveGame();
      void saveGame();
      virtual void exec();
  };
}

#endif