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
namespace States { class GameState; }

namespace Stages {
  enum ID {
    CaveID,
    FactoryID,
    TotalStages
  };

  class Stage {
    protected:
      static const float m_dt;
      static Manager::GraphicsManager* m_pGraphicsManager;
      Manager::Collision::CollisionManager m_collisionManager;
      States::GameState* m_pGameState;
      Entities::EntityFactory* m_pEntityFactory;
      std::string m_mapTxt;
      EntityList m_players;
      EntityList m_staticEntities;
      EntityList m_dynamicEntities;
      std::queue<Entities::Entity*> m_dynamicDeletionQueue;
      bool m_paused;
      sf::Music m_bgMusic;

    protected:
      void applyPhysics(Entities::Entity* pEntity);
      void drawEntities(EntityList& entityList);
      void updateEntities(EntityList& entityList);
      void updateView();
      void verifyGameOver();
      void update();
      void savePlayerData();
      void saveEntitiesData();
      void deleteEntitiesInQueue();
    
    public:
      Stage(States::GameState* pGameState, const std::string& mapTxt);
      ~Stage();

      const std::string& getMapTxt() const; 

      EntityList* getPlayers();
      EntityList* getStaticEntities();
      EntityList* getDynamicEntities();

      virtual void createRandomEnemy(sf::Vector2f& position) = 0;

      void setEntityFactory(Entities::EntityFactory* pEntityFactory);
      void spawnProjectile(Textures::ID textureID, sf::Vector2f& position, const float scale, const float speed, const float angle);
      void addToDeletionList(Entities::Entity* pEntity);
      void setPaused(const bool paused);
      void saveGame();
      // virtual void exec();
      void exec();
  };
}

#endif