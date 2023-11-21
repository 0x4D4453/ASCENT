#ifndef BEING_H
#define BEING_H

/* Program Defined */
#include "Utility/Textures.h"
#include "Utility/Constants.h"
#include "Utility/HitboxSprite.h"

/* SFML Library */
#include <SFML/Graphics.hpp>

/* Forward Declaration */
namespace Manager { class GraphicsManager; }

class Being {
  protected:
    static Manager::GraphicsManager* m_pGraphicsManager;
    static const float m_dt;
    static int m_cont;
    const int m_id;
    float m_scale;
    Textures::ID m_textureID;
    HitboxSprite m_sprite;
  
  public:
    Being(const float scale = Constants::SCALE);
    virtual ~Being();
    const int getId() const;
    const HitboxSprite* getSprite() const;
    const sf::FloatRect getGlobalHitbox() const;
    void setColor(sf::Color color);
    void setTextureID(Textures::ID textureID);
    void setTexture(sf::Texture& texture);
    void setTextureRect(const sf::IntRect& textureRect);
    void draw();
    virtual void exec() = 0;
};

#endif //BEING_H