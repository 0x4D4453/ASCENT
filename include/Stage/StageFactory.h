#ifndef STAGEFACTORY_H
#define STAGEFACTORY_H

/* Main include */
#include "Stage/Stage.h"

/* Program Defined */
#include "Entities/Entity.h"
#include "Entities/EntityFactory.h"
#include "Entities/EntityList.h"
#include "Entities/Characters/Player.h"
#include "Stage/Stage.h"
#include "Utility/ResourceHolder.h"
#include "Utility/Sounds.h"
#include "Utility/Textures.h"

namespace Manager { class GraphicsManager; }

namespace Stages {
  class StageFactory {
    private:
      static Manager::GraphicsManager* m_graphicsManager;
      Entities::EntityFactory m_entityFactory;
      ResourceHolder<Textures::ID, sf::Texture> m_textureHolder;
      ResourceHolder<Sounds::ID, sf::SoundBuffer> m_soundHolder;
      Stage* m_pStage;
      EntityList* m_pPlayers;
      EntityList* m_pStaticEntities;
      EntityList* m_pDynamicEntities;
      std::vector<sf::View>* m_pViews;
      const bool m_newGame;
      bool m_multiplayer;
      bool m_quickSave;
    
    private:
      void loadTextures();
      void loadSounds();
      void loadPlayerData(std::string& baseFilePath);
      void loadEntitiesData(std::string& baseFilePath);
      void loadSaveGame();
      void createMap(const std::string& stageTxt);
      void defineType(Entities::Entity* pEntity);
      void createPlayers();
      void createViews();
    
    public:
      StageFactory(const bool newGame = true);
      ~StageFactory();

      Stage* createStage(States::GameState* pGameState, Stages::ID stageID, const bool multiplayer, const bool quickSave);
  };
}

#endif