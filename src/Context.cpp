/* Main Include */
#include "Utility/Context.h"

/* SFML Library */
#include "SFML/Audio.hpp"

Context* Context::m_instance(NULL);

Context::Context() 
  : m_textureHolder()
  , m_fontHolder()
  , m_soundHolder()
{
  m_textureHolder.load(Textures::OnePlayer, Textures::ONE_PLAYER);
  m_textureHolder.load(Textures::TwoPlayers, Textures::TWO_PLAYERS);
  m_fontHolder.load(Fonts::Monogram, Fonts::MONOGRAM);
  m_soundHolder.load(Sounds::menuSound, Sounds::MENU);
}

Context::~Context() {

}

Context* Context::getInstance() {
    if (m_instance == NULL)
      m_instance = new Context;
    return m_instance;
} 

sf::Texture& Context::getTexture(Textures::ID textureID) {
  return m_textureHolder.getResource(textureID);
}

sf::Font& Context::getFont(Fonts::ID fontID) {
  return m_fontHolder.getResource(fontID);
}

sf::SoundBuffer& Context::getSound(Sounds::ID soundID) {
  return m_soundHolder.getResource(soundID);
}