#ifndef STAGE_H
#define STAGE_H

/* Program Defined */
#include "Entities/Entity.h"
#include "Entities/EntityList.h"
#include "Manager/Collision/CollisionManager.h"
#include "Utility/Constants.h"

/* SFML Library */
#include <SFML/Audio.hpp>

/* Forward Declaration */
namespace Manager { class GraphicsManager; }

namespace Stages {
  enum ID {
    Stage1,
    Stage2,
    Stage3,
    TotalStages
  };

  class Stage {
    protected:
      static const float m_dt;
      static Manager::GraphicsManager* m_pGraphicsManager;
      Manager::Collision::CollisionManager m_collisionManager;
      std::string m_mapTxt;
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
      void savePlayerData();
      void saveEntitiesData();
    
    public:
      Stage(const std::string& mapTxt);
      ~Stage();

      const std::string& getMapTxt() const; 
      const std::string& getEntitiesTxt() const;

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