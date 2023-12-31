/* Main Include */
#include "State/RankingState.h"

/* Program Defined */
#include "Manager/GraphicsManager.h"
#include "Utility/Constants.h"
#include "State/StateStack.h"
#include "Utility/Context.h"
#include "Utility/Fonts.h"

/* Standard Library */
#include <iostream>
#include <fstream>
#include <stdexcept>

/* JSON Library */
#include "nlohmann/json.hpp"

namespace States {
  RankingState::RankingState()
    : m_title("RANKING", m_pContext->getFont(Fonts::Monogram))
    , m_rankings()
    , m_names()
    , m_scores()
  {
    setType(StateType::Ranking);
    configureText();
    try {
      loadScoresFromJSON();
    } catch (const std::runtime_error& error) {
      std::cerr << error.what() << std::endl;
    }
  }

  RankingState::~RankingState() {

  }

  void RankingState::configureText() {
    m_title.setCharacterSize(100.f);
    centerTextOrigin(m_title);
    m_title.setPosition(static_cast<int>(Constants::WINDOW_WIDTH/2), 70);
    m_title.setFillColor(sf::Color::White);

    constexpr float characterSize = 80.f;
    int spaceBetween = 200;

    for (int i = 1; i <= 5; ++i, spaceBetween += 70) {
      sf::Text ranking = sf::Text(std::to_string(i), m_pContext->getFont(Fonts::Monogram));
      sf::Text name = sf::Text("---", m_pContext->getFont(Fonts::Monogram));
      sf::Text score = sf::Text("-----", m_pContext->getFont(Fonts::Monogram));

      ranking.setCharacterSize(characterSize);
      name.setCharacterSize(characterSize);
      score.setCharacterSize(characterSize);

      centerTextOrigin(ranking);
      centerTextOrigin(name);
      centerTextOrigin(score);
      
      ranking.setPosition(static_cast<int>(Constants::WINDOW_WIDTH/2 - 150.f), spaceBetween);
      name.setPosition(static_cast<int>(Constants::WINDOW_WIDTH/2), spaceBetween);
      score.setPosition(static_cast<int>(Constants::WINDOW_WIDTH/2 + 200.f), spaceBetween);

      m_rankings.push_back(ranking);
      m_names.push_back(name);
      m_scores.push_back(score);
    }

    m_rankings[0].setFillColor(sf::Color(255, 215, 0));
    m_names[0].setFillColor(sf::Color(255, 215, 0));
    m_scores[0].setFillColor(sf::Color(255, 215, 0));

    m_rankings[1].setFillColor(sf::Color(192, 192, 192));
    m_names[1].setFillColor(sf::Color(192, 192, 192));
    m_scores[1].setFillColor(sf::Color(192, 192, 192));

    m_rankings[2].setFillColor(sf::Color(205, 127, 50));
    m_names[2].setFillColor(sf::Color(205, 127, 50));
    m_scores[2].setFillColor(sf::Color(205, 127, 50));
  }

  void RankingState::loadScoresFromJSON() {
    using namespace nlohmann;

    std::ifstream scores("saves/highscore.json");
    if (!scores)
      throw std::runtime_error("Error loading scores!");
    
    json scoresData = json::parse(scores);
    json::iterator it = scoresData["scores"].begin();

    for (int i = 0; i < 5 && it != scoresData["scores"].end(); ++i, ++it) {
      std::string name = (*it)["name"].template get<std::string>();
      int score = (*it)["score"].template get<int>();

      m_names[i].setString(name);
      m_scores[i].setString(std::to_string(score));
    }
  }

  void RankingState::keyPressed(const sf::Keyboard::Key key) {
    m_pStateStack->pushState(StateType::Menu, NULL, true);
  }

  void RankingState::exec() {
    m_pGraphicsManager->draw(m_title);

    for (int i = 0; i < 5; ++i) {
      m_pGraphicsManager->draw((m_rankings[i]));
      m_pGraphicsManager->draw((m_names[i]));
      m_pGraphicsManager->draw((m_scores[i]));
    }
  }
} 
