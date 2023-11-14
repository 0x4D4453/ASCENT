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

/* JSON Library */
#include "nlohmann/json.hpp"

namespace States {
  RankingState::RankingState()
    : m_title("RANKING", m_pContext->getFont(Fonts::Monogram))
    , m_rankings()
    , m_names()
    , m_scores()
    , m_sprites()
  {
    configureText();
    loadScoresFromJSON();
  }

  RankingState::~RankingState() {

  }

  void RankingState::configureText() {
    m_title.setCharacterSize(100.f);
    sf::FloatRect textRect = m_title.getLocalBounds();
    m_title.setOrigin(static_cast<int>(textRect.left + textRect.width/2.0f), static_cast<int>(textRect.top  + textRect.height/2.0f));
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

      textRect = ranking.getLocalBounds();
      ranking.setOrigin(static_cast<int>(textRect.left + textRect.width/2.0f), static_cast<int>(textRect.top  + textRect.height/2.0f));
      textRect = name.getLocalBounds();
      name.setOrigin(static_cast<int>(textRect.left + textRect.width/2.0f), static_cast<int>(textRect.top  + textRect.height/2.0f));
      textRect = score.getLocalBounds();
      score.setOrigin(static_cast<int>(textRect.left + textRect.width/2.0f), static_cast<int>(textRect.top  + textRect.height/2.0f));

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
    json scoresData = json::parse(scores);
    
    int i = 0;
    json::iterator it = scoresData["scores"].begin();

    while (it != scoresData["scores"].end()) {
      std::string name = (*it)["name"];
      int score = (*it)["score"];

      m_names[i].setString(name);
      m_scores[i].setString(std::to_string(score));

      ++i;
      ++it;
    }
  }

  void RankingState::handleEvent(sf::Event& event) {
    using namespace sf;

    if (event.type == sf::Event::KeyPressed)
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
