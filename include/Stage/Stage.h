#ifndef STAGE_H
#define STAGE_H

/* Program Defined */
#include "Entities/Entity.h"
#include "Entities/Projectile.h"
#include "Entities/EntityList.h"
#include "Entities/Characters/Goomba.h"
#include "Entities/Obstacles/Spike.h"
#include "Manager/Collision/CollisionManager.h"
#include "Utility/Constants.h"
#include "Utility/ResourceHolder.h"
#include "Utility/Textures.h"

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
      ResourceHolder<Textures::ID, sf::Texture>* m_pTextureHolder;
      Entities::EntityFactory* m_pEntityFactory;
      Entities::Characters::Goomba* m_pGoomba;
      Entities::Obstacles::Spike* m_pSpike;
      States::GameState* m_pGameState;
      std::string m_mapTxt;
      std::queue<Entities::Entity*> m_dynamicDeletionQueue;
      std::vector<sf::View> m_views;
      sf::Music m_bgMusic;
      EntityList m_players;
      EntityList m_staticEntities;
      EntityList m_dynamicEntities;
      const int m_maxGoombaInstances;
      const int m_maxSpikeInstances;
      const int m_goombaChance;
      const int m_spikeChance;
      int m_goombaNumber;
      int m_spikeNumber;
      bool m_paused;

    protected:
      virtual void createGoomba(sf::Vector2f& position);
      virtual void createSpike(sf::Vector2f& position);
      void applyPhysics(Entities::Entity* pEntity);
      void drawEntities(EntityList& entityList);
      void updateEntities(EntityList& entityList);
      void updateView();
      void verifyGameOver();
      void update();
      void draw();
      void savePlayerData();
      void saveEntitiesData();
      void deleteEntitiesInQueue();
      void checkOutOfBounds(Entities::Entity* pEntity);
    
    public:
      Stage(
        ResourceHolder<Textures::ID, sf::Texture>* pTextureHolder,
        Entities::EntityFactory* pEntityFactory,
        States::GameState* pGameState,
        const std::string& mapTxt
      );
      ~Stage();

      const std::string& getMapTxt() const; 

      EntityList* getPlayers();
      EntityList* getStaticEntities();
      EntityList* getDynamicEntities();
      std::vector<sf::View>* getViews();

      virtual void loadTextures() = 0;
      virtual void createRandomEnemy(sf::Vector2f& position) = 0;
      virtual void createRandomObstacle(sf::Vector2f& position) = 0;

      void spawnProjectile(Textures::ID textureID, sf::Vector2f& position, const float scale, const float speed, const float angle);
      void addToDeletionList(Entities::Entity* pEntity);
      void setPaused(const bool paused);
      void saveGame();
      // virtual void exec();
      void exec();
  };
}

#endif