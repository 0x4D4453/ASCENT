#ifndef PLAYER_H
#define PLAYER_H

/* Program Defined */
#include "Entities/Characters/Character.h"

/* Standard Library */
#include <map>
#include <unordered_map>

/* SFML Library */
#include <SFML/Audio.hpp>

/* JSON Library */
#include "nlohmann/json.hpp"

/* Forward Declaration */
namespace Entities { namespace Characters { class Enemy; } }

namespace Entities {
  namespace Characters {
    class Player : public Character {
      private:
        enum Actions {
          MoveLeft,
          MoveRight,
          Jump
        };

      private:
        std::map<Actions, sf::Keyboard::Key> m_keyBinding;
        std::unordered_map<Actions, void(Player::*)()> m_actionBinding;
        int m_points;
        bool m_isCharging;
        float m_jumpHeight;
        const float m_chargingSpeed;
        const float m_minJumpHeight;
        const float m_maxJumpHeight;
        const float m_attackSpeed;
        const float m_maxWalkingSpeed;
        sf::Sound m_jumpSound;

      private:
        virtual void update();
        void moveLeft();
        void moveRight();
        void chargeJump();
        void jump();
        void handleInput();
        const float getCurrentSpeed() const;
        void attack(Enemy *pEnemy);
      
      public:
        Player(
                sf::Texture& playerTexture
              , sf::SoundBuffer& jumpSoundBuffer
              , sf::Keyboard::Key moveLeftKey = sf::Keyboard::A
              , sf::Keyboard::Key moveRightKey = sf::Keyboard::D
              , sf::Keyboard::Key jumpKey = sf::Keyboard::W);
        ~Player();
        const bool getIsCharging() const;
        void setIsCharging(const bool isCharging);
        const bool isAttacking();
        virtual void collide(Entity *pEntity, Manager::Collision::CollisionType type, float overlap);
        virtual void save(nlohmann::ordered_json& jsonData);
        virtual void loadSave(const nlohmann::ordered_json& jsonData);
    };
  }
}

#endif 