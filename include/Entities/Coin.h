#ifndef COIN_H
#define COIN_H

/* Program Defined */
#include "Entities/Entity.h"

/* SFML Library */
#include "SFML/Audio.hpp"

/* Forward Declaration */
namespace Stages { class Stage; }

namespace Entities {
  class Coin : public Entity {
      private:
        const int m_value;
        sf::Sound m_coinSound;
        Stages::Stage* m_pStage;
        bool m_visible;
    
      public:
        Coin(Textures::ID textureID, sf::Texture& texture, sf::Vector2f position, sf::SoundBuffer& soundBuffer, Stages::Stage* pStage);
        ~Coin();
        virtual void reactToCollision(Entity *pEntity, Manager::Collision::CollisionType type, float overlap);
        virtual void save(nlohmann::ordered_json& jsonData);
        virtual void loadSave(const nlohmann::ordered_json& jsonData);
        virtual void exec();
  };
}

#endif 