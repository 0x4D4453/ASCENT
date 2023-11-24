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
        bool m_isAttacking;
        bool m_isCharging;
        bool m_isImmune;
        float m_jumpHeight;
        float m_blinkElapsedTime;
        float m_immunityElapsedTime;
        const float m_chargingSpeed;
        const float m_minJumpHeight;
        const float m_maxJumpHeight;
        const float m_attackSpeed;
        const float m_maxWalkingSpeed;
        const float m_immunityLimitTime;
        sf::Sound m_jumpSound;

      private:
        virtual void update();
        virtual void handleDamage(const int damage);
        void moveLeft();
        void moveRight();
        void chargeJump();
        void jump();
        void handleInput();
        void checkIsAttacking();
        void enemyCollision(Entity* pEntity, Manager::Collision::CollisionType type);
        void attack(Enemy* pEnemy);
        void updateImmunity();
        void addPoints(Enemy* pEnemy);
      
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
        const bool getIsAttacking() const;
        const bool getIsImmune() const;
        const int getPoints() const;
        virtual void reactToCollision(Entity *pEntity, Manager::Collision::CollisionType type, float overlap);
        virtual void save(nlohmann::ordered_json& jsonData);
        virtual void loadSave(const nlohmann::ordered_json& jsonData);
    };
  }
}

#endif 