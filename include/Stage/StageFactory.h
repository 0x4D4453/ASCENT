#ifndef STAGEFACTORY_H
#define STAGEFACTORY_H

/* Main include */
#include "Stage/Stage.h"

/* Program Defined */
#include "Entities/Entity.h"
#include "Entities/EntityFactory.h"
#include "Entities/EntityList.h"
#include "Entities/Player.h"
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
      EntityList* m_players;
      EntityList* m_staticEntities;
      EntityList* m_dynamicEntities;
      bool m_newGame;
    
    private:
      void loadTextures();
      void loadSounds();
      void createMap(const char* stageTxt);
      void defineType(Entities::Entity* pEntity);
      void createPlayers(int stageHeight);
    
    public:
      StageFactory(const bool newGame = true);
      ~StageFactory();

      Stage* createStage(const char* stageTxt);
  };
}

#endif