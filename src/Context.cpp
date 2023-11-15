/* Main Include */
#include "Utility/Context.h"

/* Program Defined */
#include "Utility/Constants.h"

/* SFML Library */
#include "SFML/Audio.hpp"

Context* Context::m_instance(NULL);

Context::Context() 
  : m_textureHolder()
  , m_fontHolder()
  , m_soundHolder()
  , m_multiplayer(false)
  , m_stagePath(Constants::STAGE_3)
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

void Context::setMultiplayer(const bool multiplayer) {
  m_multiplayer = multiplayer;
}

const bool Context::getMultiplayer() const {
  return m_multiplayer;
}

void Context::setStage(const std::string& stage) {
  m_stagePath = stage;
}

std::string& Context::getStage() {
  return m_stagePath;
}