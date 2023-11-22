#ifndef PROJECTILE_H
#define PROJECTILE_H

/* Program Defined */
#include "Entities/Entity.h"
#include "Entities/Characters/Player.h"
#include "Entities/EntityList.h"
#include "Utility/Constants.h"

/* SFML Library */
#include <SFML/Graphics.hpp>

/* Forward Declaration */
namespace Stages { class Stage; }

namespace Entities {
  class Projectile : public Entity {
    private:
      const float m_timeLimit;
      const float m_maxRange;
      const float m_angle;
      const float m_attack;
      Stages::Stage* m_pStage;
      float m_distance;
      float m_timeElapsed;
      bool m_waitingDeletion;

    private:
      void autoRemove();
      void checkOutOfBounds();
      void checkTimeLimit();
      void playerCollide(Characters::Player* pPlayer, Manager::Collision::CollisionType type);
      void damagePlayer(Characters::Player* pPlayer);
    
    public:
      Projectile(
        Textures::ID textureID, sf::Texture& texture,
        sf::Vector2f position = sf::Vector2f(0.f, 0.f),
        const float scale = Constants::SCALE / 4.f,
        const float speed = 0.f,
        const float angle = 0.f
      );
      ~Projectile();
      void setStage(Stages::Stage* pStage);
      virtual void collide(Entity *pEntity, Manager::Collision::CollisionType type, float overlap);
      virtual void save(nlohmann::ordered_json& jsonData);
      virtual void loadSave(const nlohmann::ordered_json& jsonData);
      virtual void exec();
  };
};

#endif