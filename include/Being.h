#ifndef BEING_H
#define BEING_H

/* Program Defined */
#include "Utility/Textures.h"

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
    Textures::ID m_textureID;
    sf::Sprite m_sprite;
  
  public:
    Being();
    virtual ~Being();
    const int getId() const;
    const sf::Sprite* getSprite() const;
    const sf::FloatRect getGlobalBounds() const;
    void setTextureID(Textures::ID textureID);
    void setTexture(sf::Texture& texture);
    void setTextureRect(const sf::IntRect& textureRect);
    void draw();
    virtual void exec() = 0;
};

#endif //BEING_H