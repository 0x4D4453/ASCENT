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
  , m_stageID(Stages::CaveID)
  , m_totalScore(0)
  , m_quickSaveAvailable(false)
{
  m_textureHolder.load(Textures::OnePlayer, Textures::ONE_PLAYER);
  m_textureHolder.load(Textures::TwoPlayers, Textures::TWO_PLAYERS);
  m_textureHolder.load(Textures::LeftArrow, Textures::LEFT_ARROW);
  m_textureHolder.load(Textures::RightArrow, Textures::RIGHT_ARROW);
  m_textureHolder.load(Textures::StagePlaceholder, Textures::STAGE_PLACEHOLDER);
  m_textureHolder.load(Textures::StagePlaceholder2, Textures::STAGE_PLACEHOLDER2);
  m_fontHolder.load(Fonts::Monogram, Fonts::MONOGRAM);
  m_soundHolder.load(Sounds::menuSound, Sounds::MENU);
  m_soundHolder.load(Sounds::Pause, Sounds::PAUSE);;
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

void Context::setStage(const Stages::ID stageID) {
  m_stageID = stageID;
}

const Stages::ID Context::getStage() const {
  return m_stageID;
}

void Context::setScore(const int score) {
  m_totalScore = score;
}

const int Context::getScore() const {
  return m_totalScore;
}

void Context::setQuickSave(const bool quickSave) {
  m_quickSaveAvailable = quickSave;
}

const bool Context::getQuickSave() const {
  return m_quickSaveAvailable;
}