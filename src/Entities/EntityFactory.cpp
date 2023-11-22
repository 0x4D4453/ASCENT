/* Main Include */
#include "Entities/EntityFactory.h"

/* Program Defined */
#include "Entities/Characters/Goomba.h"
#include "Entities/Characters/Fly.h"
#include "Entities/Characters/Tyrant.h"
#include "Entities/Obstacles/MovingPlatform.h"
#include "Entities/Obstacles/Platform.h"
#include "Entities/Obstacles/Spike.h"
#include "Entities/Projectile.h"

/* Standard Library */
#include <iostream>

namespace Entities {
  EntityFactory::EntityFactory()
    : m_pTextureHolder(NULL)
    , m_pSoundHolder(NULL)
    , m_pEntity(NULL)
  {

  }

  EntityFactory::~EntityFactory() {
    m_pTextureHolder = NULL;
    m_pSoundHolder = NULL;
    m_pEntity = NULL;
  }

  void EntityFactory::setTextureHolder(ResourceHolder<Textures::ID, sf::Texture>* pTextureHolder) {
    if (pTextureHolder)
      m_pTextureHolder = pTextureHolder;
  }

  void EntityFactory::setSoundHolder(ResourceHolder<Sounds::ID, sf::SoundBuffer>* pSoundHolder) {
    if (pSoundHolder)
      m_pSoundHolder = pSoundHolder;
  }

  Entity* EntityFactory::createEntity(Entities::EntityID entityID, Textures::ID textureID, sf::Vector2f& position, Stages::Stage* pStage) {
    m_pEntity = NULL;
    sf::Texture& textureRef = m_pTextureHolder->getResource(textureID);

    switch (entityID) {
      case (PlatformE): 
        m_pEntity = static_cast<Entity*>(new Obstacles::Platform(textureID, textureRef, position));
        break;
      case (GoombaE):
        m_pEntity = static_cast<Entity*>(new Characters::Goomba(textureID, textureRef, position));
        break;
      case (FlyE):
        m_pEntity = static_cast<Entity*>(new Characters::Fly(textureID, textureRef, position));
        break;
      case (TyrantE):
        m_pEntity = static_cast<Entity*>(new Characters::Tyrant(textureID, textureRef, position, pStage));
        break;
      case (EnemyE):
        m_pEntity = static_cast<Entity*>(new Characters::Goomba(textureID, textureRef, position));
        break;
      case (MovingPlatformE): 
        m_pEntity = static_cast<Entity*>(new Obstacles::MovingPlatform(textureID, textureRef, position));
        break;
      case (SpikesE): 
        m_pEntity = static_cast<Entity*>(new Obstacles::Spike(textureID, textureRef, position));
        break;
    }
    
    if (m_pEntity == NULL) {
      std::cerr << "Error creating entity with ID: " << static_cast<int>(entityID) << std::endl;
      exit(1);
    }

    return m_pEntity;
  }

  Projectile* EntityFactory::createProjectile(Textures::ID textureID, sf::Vector2f& position, const float scale, const float speed, const float angle) {
    sf::Texture& textureRef = m_pTextureHolder->getResource(textureID);
    return new Projectile(textureID, textureRef, position, scale, speed, angle);
  }

  sf::Texture& EntityFactory::getTexture(Textures::ID textureID) {
    return m_pTextureHolder->getResource(textureID);
  }
}