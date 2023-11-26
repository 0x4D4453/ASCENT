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
    
    private:
      void configureText();
      void loadScoresFromJSON();
    
    public:
      RankingState();
      ~RankingState();
      virtual void keyPressed(const sf::Keyboard::Key key);
      virtual void exec();
  };
}
#endif