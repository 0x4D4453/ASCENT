#ifndef STATESTACK_H
#define STATESTACK_H

/* Program Defined */
#include "State/State.h"

/* SFML Library */
#include <SFML/Graphics.hpp>
#include <SFML/System/NonCopyable.hpp>

/* Standard Library */
#include <vector>
#include <queue>

namespace States {
  class StateStack : sf::NonCopyable {
    private:
      enum class Command {
        Push,
        Pop,
        Clear,
        TotalCommands
      };
    
    private:
      struct CommandDetails {
        Command command;
        StateType stateType;
        State* pState;
      };

    private:
      static StateStack* m_instance;
      std::vector<State*> m_stack;
      std::queue<CommandDetails> m_commandQueue;

    private:
      StateStack();
      void createState(StateType stateType, State* pState);
      void delayedPopState();
      void clearStates();
      void applyPendingCommands();
  
    public:
      ~StateStack();
      static StateStack* getInstance();
      void pushState(StateType stateType, State* pState = NULL, const bool isReplacing = false);
      void popState();
      void exec();
      State* getBack() const;
  };
}

#endif 