#ifndef CONTEXT_H
#define CONTEXT_H

/* Program Defined */
#include "Utility/Fonts.h"
#include "Utility/Sounds.h"
#include "Utility/Textures.h"
#include "Utility/ResourceHolder.h"

/* SFML Library */
#include "SFML/Audio.hpp"

class Context {
  private:
    static Context* m_instance;
    ResourceHolder<Textures::ID, sf::Texture> m_textureHolder;
    ResourceHolder<Fonts::ID, sf::Font> m_fontHolder;
    ResourceHolder<Sounds::ID, sf::SoundBuffer> m_soundHolder;

    bool m_multiplayer;
    std::string m_stagePath;
  
  private:
    Context();
  
  public:
    ~Context();
    static Context* getInstance();
    sf::Texture& getTexture(Textures::ID textureID);
    sf::Font& getFont(Fonts::ID fontID);
    sf::SoundBuffer& getSound(Sounds::ID soundID);

    void setMultiplayer(const bool multiplayer);
    const bool getMultiplayer() const;
    void setStage(const std::string& stage);
    std::string& getStage();
};

#endif