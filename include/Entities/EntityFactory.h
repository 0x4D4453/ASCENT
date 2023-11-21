#ifndef ENTITYFACTORY_H
#define ENTITYFACTORY_H

/* Program Defined */
#include "Entities/Entity.h"
#include "Entities/Projectile.h"
#include "Stage/Stage.h"
#include "Utility/Textures.h"
#include "Utility/Sounds.h"
#include "Utility/ResourceHolder.h"

/* SFML Library */
#include "SFML/Audio.hpp"

namespace Entities {
  class EntityFactory {
    private:
      ResourceHolder<Textures::ID, sf::Texture>* m_pTextureHolder;
      ResourceHolder<Sounds::ID, sf::SoundBuffer>* m_pSoundHolder;
      Entity* m_pEntity;

    public:
      EntityFactory();
      ~EntityFactory();
      void setTextureHolder(ResourceHolder<Textures::ID, sf::Texture>* pTextureHolder);
      void setSoundHolder(ResourceHolder<Sounds::ID, sf::SoundBuffer>* pSoundHolder);
      Entity* createEntity(Entities::EntityID entityID, Textures::ID textureID, sf::Vector2f& position, Stages::Stage* pStage = NULL);
      Projectile* createProjectile(Textures::ID textureID, sf::Vector2f& position, const float scale, const float speed, const float angle);
  };
}

#endif