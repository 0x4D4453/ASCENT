/* Main Include */
#include "Entities/EntityFactory.h"

/* Program Defined */
#include "Entities/Characters/Goomba.h"
#include "Entities/Characters/Fly.h"
#include "Entities/Obstacles/MovingPlatform.h"
#include "Entities/Obstacles/Platform.h"
#include "Entities/Obstacles/Spike.h"

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

  Entity* EntityFactory::createEntity(Entities::EntityID entityID, Textures::ID textureID, sf::Vector2f& position) {
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
      case (EnemyE):
        m_pEntity = static_cast<Entity*>(new Characters::Goomba(textureID, textureRef, position));
        break;
      case (MovingPlatformE): 
        m_pEntity = static_cast<Entity*>(new Obstacles::MovingPlatform(m_pTextureHolder->getResource(textureID), position));
        break;
      case (SpikesE): 
        m_pEntity = static_cast<Entity*>(new Obstacles::Spike(m_pTextureHolder->getResource(textureID), position));
        break;
    }
    
    if (m_pEntity == NULL) {
      std::cerr << "Error creating entity with ID: " << static_cast<int>(entityID) << std::endl;
      exit(1);
    }

    return m_pEntity;
  }
}