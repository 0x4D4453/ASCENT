#ifndef STAGE_H
#define STAGE_H

/* Program Defined */
#include "Entities/Entity.h"
#include "Entities/Projectile.h"
#include "Entities/EntityList.h"
#include "Manager/Collision/CollisionManager.h"
#include "Utility/Constants.h"

/* SFML Library */
#include <SFML/Audio.hpp>

/* Standard Library */
#include <queue>

/* Forward Declaration */
namespace Manager { class GraphicsManager; }
namespace Entities { class EntityFactory; }

namespace Stages {
  enum ID {
    Stage1,
    Stage2,
    Stage3,
    Stage4,
    TotalStages
  };

  class Stage {
    protected:
      static const float m_dt;
      static Manager::GraphicsManager* m_pGraphicsManager;
      Manager::Collision::CollisionManager m_collisionManager;
      Entities::EntityFactory* m_pEntityFactory;
      std::string m_mapTxt;
      EntityList m_players;
      EntityList m_staticEntities;
      EntityList m_dynamicEntities;
      std::queue<Entities::Entity*> m_dynamicDeletionQueue;
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
      void deleteEntitiesInQueue();
    
    public:
      Stage(const std::string& mapTxt);
      ~Stage();

      const std::string& getMapTxt() const; 
      const std::string& getEntitiesTxt() const;

      EntityList* getPlayers();
      EntityList* getStaticEntities();
      EntityList* getDynamicEntities();

      void setEntityFactory(Entities::EntityFactory* pEntityFactory);
      void spawnProjectile(Textures::ID textureID, sf::Vector2f& position, const float scale, const float speed, const float angle);
      void addToDeletionList(Entities::Entity* pEntity);
      void setPaused(const bool paused);
      void loadSaveGame();
      void saveGame();
      // virtual void exec();
      void exec();
  };
}

#endif