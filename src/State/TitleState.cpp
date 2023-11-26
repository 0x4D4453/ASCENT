/* Main Include */
#include "State/TitleState.h"

/* Program Defined */
#include "State/StateStack.h"
#include "Utility/Context.h"
#include "Utility/Constants.h"

namespace States {
  TitleState::TitleState()
    : m_title(Constants::GAME_NAME, m_pContext->getFont(Fonts::Monogram))
    , m_pressStart("Press Any Key to Start", m_pContext->getFont(Fonts::Monogram))
    , m_startVisible(true)
    , m_maxEffectTime(0.f)
  {
    setType(StateType::Title);

    m_title.setCharacterSize(500.f);
    centerTextOrigin(m_title);
    m_title.setPosition(static_cast<int>(Constants::WINDOW_WIDTH/2.f), static_cast<int>(250.f));
    
    m_pressStart.setCharacterSize(50.f);
    centerTextOrigin(m_pressStart);
    m_pressStart.setPosition(static_cast<int>(Constants::WINDOW_WIDTH/2.f),  static_cast<int>(Constants::WINDOW_HEIGHT - 100.f));
  }

  TitleState::~TitleState() {

  }

  void TitleState::keyPressed(const sf::Keyboard::Key key) {
    m_pStateStack->pushState(StateType::Menu, NULL, true);
  }

  void TitleState::update() {
    sf::Time* timeSinceLastUpdate = m_pGraphicsManager->getTimeSinceLastUpdate();
    const sf::Time* timePerFrame = m_pGraphicsManager->getTimePerFrame();

    while (*timeSinceLastUpdate >= *timePerFrame) {
      m_maxEffectTime += timePerFrame->asSeconds();

      if (m_maxEffectTime >= 0.5f) {
        m_startVisible = !m_startVisible;
        m_maxEffectTime = 0.f;
      }

      (*timeSinceLastUpdate) -= (*timePerFrame);
    }
  }

  void TitleState::exec() {
    update();
    m_pGraphicsManager->draw(m_title);
    if (m_startVisible)
      m_pGraphicsManager->draw(m_pressStart);
  }
}