#ifndef CONTEXT_H
#define CONTEXT_H

/* Program Defined */
#include "Utility/Fonts.h"
#include "Utility/Sounds.h"
#include "Utility/ResourceHolder.h"

/* SFML Library */
#include "SFML/Audio.hpp"

class Context {
  private:
    static Context* m_instance;
    ResourceHolder<Fonts::ID, sf::Font> m_fontHolder;
    ResourceHolder<Sounds::ID, sf::SoundBuffer> m_soundHolder;
  
  private:
    Context();
  
  public:
    ~Context();
    static Context* getInstance();
    sf::Font& getFont(Fonts::ID fontID);
    sf::SoundBuffer& getSound(Sounds::ID soundID);
};

#endif