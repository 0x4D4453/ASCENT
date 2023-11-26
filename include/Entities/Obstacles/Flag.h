#ifndef FLAG_H
#define FLAG_H

/* Program Defined */
#include "Entities/Obstacles/Obstacle.h"
#include "Utility/Threads/Thread.h"

/* SFML Library */
#include "SFML/Audio.hpp"

/* Foward Declaration */
namespace Stages { class Stage; }
class Context;

namespace Entities {
  namespace Obstacles {
    class Flag : public Obstacle, public Threads::Thread {
      private:
        Stages::Stage* m_pStage;
        Context* m_pContext;
        bool m_reached;
        sf::Sound m_saveSound;

      public:
        Flag(Textures::ID textureID, sf::Texture& texture, sf::Vector2f position, sf::SoundBuffer& soundBuffer, Stages::Stage* pStage);
        ~Flag();
        virtual void run();
        void quickSave();
        virtual void reactToCollision(Entity *pEntity, Manager::Collision::CollisionType type, float overlap);
        virtual void save(nlohmann::ordered_json& jsonData);
        virtual void loadSave(const nlohmann::ordered_json& jsonData);
        virtual void exec();
    };
  }
}

#endif