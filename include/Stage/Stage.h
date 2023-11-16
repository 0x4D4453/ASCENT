#ifndef STAGE_H
#define STAGE_H

/* Program Defined */
#include "Entities/Entity.h"
#include "Entities/EntityList.h"
#include "Manager/Collision/CollisionManager.h"

/* SFML Library */
#include <SFML/Audio.hpp>

/* Forward Declaration */
namespace Manager { class GraphicsManager; }

namespace Stages {
  class Stage {
    protected:
      static Manager::GraphicsManager* m_pGraphicsManager;
      static const float m_dt;
      Manager::Collision::CollisionManager m_collisionManager;
      EntityList m_players;
      EntityList m_staticEntities;
      EntityList m_dynamicEntities;
      bool m_paused;
      sf::Music m_bgMusic;

    protected:
      virtual void setup() = 0;
      void applyPhysics(Entities::Entity* pEntity);
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
      // virtual void exec();
      void exec();
  };
}

#endif