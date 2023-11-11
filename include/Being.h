#ifndef BEING_H
#define BEING_H

/* SFML Library */
#include <SFML/Graphics.hpp>

/* Forward Declaration */
namespace Manager { class GraphicsManager; }

class Being {
  protected:
    static Manager::GraphicsManager* m_pGraphicsManager;
    static const float m_dt;
    const int m_id;
    sf::Sprite m_sprite;
    sf::Texture m_texture;
  
  public:
    Being();
    virtual ~Being();
    const sf::Sprite* getSprite() const;
    const sf::FloatRect getGlobalBounds() const;
    void setTexture(const char* file);
    void setTexture(sf::Texture* texture);
    void draw();
    virtual void exec() = 0;
};

#endif //BEING_H