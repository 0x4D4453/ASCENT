#ifndef RANKINGSTATE_H
#define RANKINGSTATE_H

/* Program Defined */
#include "State/State.h" 

/* Standard Library */
#include <vector>

namespace States {
  class RankingState : public State {
    private:
      sf::Text m_title;
      std::vector<sf::Text> m_rankings;
      std::vector<sf::Text> m_names;
      std::vector<sf::Text> m_scores;
      std::vector<sf::Sprite> m_sprites;
    
    private:
      void configureText();
      void loadScoresFromJSON();
      void configureSprite();
    
    public:
      RankingState();
      ~RankingState();
      virtual void handleEvent(sf::Event& event);
      virtual void exec();
  };
}
#endif