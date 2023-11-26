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

// Conceitos gerais advindos do livro SFML Game Development.
// MOREIRA, A.; HANSSON, H. V.; HALLER, J. SFML Game Development. Packt Publishing. 2013. ISBN 978-1849696845 
namespace States {
  class StateStack : public sf::NonCopyable {
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
      Context* m_pContext;

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