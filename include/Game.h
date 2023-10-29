#ifndef GAME_H
#define GAME_H

/* Program Defined */
#include "Manager/GraphicsManager.h"
#include "State/StateStack.h"

/* SFML Library */
#include <SFML/System/NonCopyable.hpp>

class Game : sf::NonCopyable {
  private:
    Manager::GraphicsManager* m_pGraphicsManager;
    States::StateStack* m_pStateStack;
  
  public:
    Game();
    ~Game();
    void run();
};

#endif //GAME_H