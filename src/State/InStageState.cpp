/* Main Include */
#include "State/InStageState.h"

/* Program Defined */
#include "Manager/GraphicsManager.h"
#include "State/StateStack.h"
#include "Utility/Constants.h"
#include "Utility/Context.h"
#include "Utility/Fonts.h"

namespace States {
    InStageState::InStageState(const int maxOption, States::GameState* pGameState, const char* titleString) 
    : OptionsState(maxOption)
    , m_pGameState(pGameState)
    , m_background()
    , m_title(titleString, m_pContext->getFont(Fonts::Monogram))
  {
    setup();
  }

  InStageState::~InStageState() {

  }

  void InStageState::setup() {
    m_pGraphicsManager->resetView();
    sf::Vector2f viewCenterPosition = m_pGraphicsManager->getViewCenter();
    
    m_background.setSize(sf::Vector2f(Constants::WINDOW_WIDTH, Constants::WINDOW_HEIGHT));
    m_background.setFillColor(sf::Color(0.f, 0.f, 0.f, 150.f)); 
    m_background.setPosition(m_pGraphicsManager->getViewCoordinates().x, m_pGraphicsManager->getViewCoordinates().y);

    m_title.setCharacterSize(80.f);
    centerTextOrigin(m_title);
    m_title.setPosition(static_cast<int>(viewCenterPosition.x), static_cast<int>(viewCenterPosition.y - 250.f));
  } 

  void InStageState::exec() {
    m_pGraphicsManager->resetView();
    m_pGraphicsManager->draw(m_background);
    m_pGraphicsManager->draw(m_title);

    std::vector<sf::Text*>::iterator it = m_options.begin();

    while (it != m_options.end()) {
      m_pGraphicsManager->draw(*(*it));
      ++it;
    }

    sf::Time* timeSinceLastUpdate = m_pGraphicsManager->getTimeSinceLastUpdate();
    const sf::Time* timePerFrame = m_pGraphicsManager->getTimePerFrame();

    while (*timeSinceLastUpdate >= *timePerFrame)
      (*timeSinceLastUpdate) -= (*timePerFrame);
  }
}