/* Main Include */
#include "State/StageSelectState.h"

/* Program Defined */
#include "Stage/Stage.h"
#include "State/StateStack.h"
#include "Utility/Constants.h"
#include "Utility/Context.h"
#include "Utility/Fonts.h"

/* Standard Library */
#include <iostream>

namespace States {
  StageSelectState::StageSelectState()
    : OptionsState(static_cast<int>(TotalOptions))
    , m_leftArrow(m_pContext->getTexture(Textures::LeftArrow))
    , m_rightArrow(m_pContext->getTexture(Textures::RightArrow))
    , m_stageImages()
  {
    setType(StateType::StageSelect);
    setup();
  }

  StageSelectState::~StageSelectState() {

  }

  void StageSelectState::setup() {
    constexpr float distanceFromTop = Constants::WINDOW_HEIGHT/2.f;

    m_leftArrow.setScale(sf::Vector2f(Constants::SCALE * 2.f, Constants::SCALE * 2.f));
    m_rightArrow.setScale(sf::Vector2f(Constants::SCALE * 2.f, Constants::SCALE * 2.f));
    m_leftArrow.setOrigin(sf::Vector2f(Constants::SPRITE_SIZE/2.f, 0));
    m_leftArrow.setPosition(sf::Vector2f(150.f, Constants::WINDOW_HEIGHT/2.f));
    m_rightArrow.setOrigin(sf::Vector2f(Constants::SPRITE_SIZE/2.f, 0));
    m_rightArrow.setPosition(sf::Vector2f(Constants::WINDOW_WIDTH - 150.f, Constants::WINDOW_HEIGHT/2.f));

    m_stageImages.push_back(sf::Sprite(m_pContext->getTexture(Textures::StagePlaceholder)));
    m_stageImages.push_back(sf::Sprite(m_pContext->getTexture(Textures::StagePlaceholder2)));

    for (int i = 0; i < static_cast<int>(TotalOptions); ++i) {
      m_stageImages[i].setOrigin(400.f/2.f, 0);
      m_stageImages[i].setPosition(Constants::WINDOW_WIDTH/2.f, distanceFromTop - 250.f);
    }

    m_outlineRect.setSize(sf::Vector2f(400.f, 400.f));
    m_outlineRect.setOrigin(400.f/2.f, 0);
    m_outlineRect.setPosition(Constants::WINDOW_WIDTH/2.f, distanceFromTop - 250.f);
    m_outlineRect.setFillColor(sf::Color::Transparent);
    m_outlineRect.setOutlineThickness(3.f);
    m_outlineRect.setOutlineColor(sf::Color::White);

    createOption("Cave", sf::Vector2f(Constants::WINDOW_WIDTH/2.f, distanceFromTop + 205.f));
    createOption("Factory", sf::Vector2f(Constants::WINDOW_WIDTH/2.f, distanceFromTop + 205.f));
  }

  void StageSelectState::changeState() {
    switch (m_currentOption) {
      case (Cave):
        m_pContext->setStage(Stages::CaveID);
        break;
      case (Factory):
        m_pContext->setStage(Stages::FactoryID);
        break;
      default: break;
    }

    m_pStateStack->pushState(StateType::Loading, NULL, true);
  }

  void StageSelectState::keyPressed(const sf::Keyboard::Key key) {
    switch (key) {
      case (sf::Keyboard::A): 
        movePreviousOption(); 
        break;
      case (sf::Keyboard::D): 
        moveNextOption(); 
        break;
      case (sf::Keyboard::Enter): 
        changeState(); 
        break;
      case (sf::Keyboard::Escape): 
        m_pStateStack->pushState(StateType::PlayerSelect, NULL, true); 
      break;
      default: break;
    }
  }

  void StageSelectState::exec() {
    if (m_currentOption > Cave)
      m_pGraphicsManager->draw(m_leftArrow);
    
    if (m_currentOption < Factory)
      m_pGraphicsManager->draw(m_rightArrow);

    m_pGraphicsManager->draw(m_stageImages[m_currentOption]);
    m_pGraphicsManager->draw(m_outlineRect);
    m_pGraphicsManager->draw(*(m_options[m_currentOption]));
  }
}