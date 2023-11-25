#ifndef FLAG_H
#define FLAG_H

/* Program Defined */
#include "Entities/Obstacles/Obstacle.h"
#include "Utility/Threads/Thread.h"

/* Foward Declaration */
namespace Stages { class Stage; }

namespace Entities {
  namespace Obstacles {
    class Flag : public Obstacle, public Threads::Thread {
      private:
        Stages::Stage* m_pStage;
        bool m_reached;

      public:
        Flag(Textures::ID textureID, sf::Texture& texture, sf::Vector2f position, Stages::Stage* pStage);
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