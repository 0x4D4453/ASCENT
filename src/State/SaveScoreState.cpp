/* Main Include */
#include "State/SaveScoreState.h"

/* Program Defined */
#include "Manager/GraphicsManager.h"
#include "State/GameState.h"
#include "State/StateStack.h"
#include "Utility/Constants.h"
#include "Utility/Context.h"
#include "Utility/Fonts.h"

/* Standard Library */
#include <fstream>
#include <map>

/* JSON Library */
#include "nlohmann/json.hpp"

namespace States {
  SaveScoreState::SaveScoreState() 
    : m_textInput(m_pContext->getFont(Fonts::Monogram), sf::Vector2f(Constants::WINDOW_WIDTH/2.f, 300.f))
    , m_playerName("Player Name", m_pContext->getFont(Fonts::Monogram))
  {
    setType(StateType::SaveScore);
    setup();
  }

  SaveScoreState::~SaveScoreState() {

  }

  void SaveScoreState::setup() {
    m_pGraphicsManager->resetView();
    m_playerName.setCharacterSize(80.f);
    centerTextOrigin(m_playerName);
    m_playerName.setPosition(static_cast<int>(Constants::WINDOW_WIDTH/2.f), 200.f);
  }

  void SaveScoreState::textEntered(const char character) {
    if (character >= 97 && character < 128)
      m_textInput.addCharacter(character);
    else if (character == 8)
      m_textInput.deleteCharacter();
  }

  void SaveScoreState::saveScore() {
    if (m_textInput.getString().size() <= 0)
      return;

    using namespace nlohmann;
    using namespace std;

    ifstream scoresStream("saves/highscore.json");
    json scoresJson = json::parse(scoresStream);
    multimap<int, string> scoresMap;

    json::iterator it;

    for (it = scoresJson["scores"].begin(); it != scoresJson["scores"].end(); ++it)
      scoresMap.insert(make_pair((*it)["score"].template get<int>(), (*it)["name"].template get<string>()));
    
    scoresMap.insert(make_pair(m_pContext->getScore(), m_textInput.getString()));
    
    json scores;
    json playerScore;
    multimap<int, string>::reverse_iterator reverseIterator;
  
    for (reverseIterator = scoresMap.rbegin(); reverseIterator != scoresMap.rend(); ++reverseIterator) {
      playerScore["name"] = reverseIterator->second;
      playerScore["score"] = reverseIterator->first;
      scores["scores"].push_back(playerScore);
    }

    std::ofstream jsonOut("saves/highscore.json");
    jsonOut << std::setw(2) << scores;

    jsonOut.close();
    scoresStream.close();
  }

  void SaveScoreState::changeState() {
    m_pStateStack->pushState(StateType::Menu, NULL, true);
  }

  void SaveScoreState::keyPressed(const sf::Keyboard::Key key) {
    switch (key) {
      case (sf::Keyboard::Enter):
        saveScore();
        changeState();
        break;
      default: break;
    }
  }

  void SaveScoreState::exec() {
    std::vector<sf::Text*>::iterator it = m_options.begin();

    while (it != m_options.end()) {
      m_pGraphicsManager->draw(*(*it));
      ++it;
    }

    m_pGraphicsManager->draw(m_playerName);
    m_textInput.exec(*m_pGraphicsManager->getWindow(), m_pGraphicsManager->getTimePerFrame()->asSeconds());
  }
}