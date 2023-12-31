/* Main Include */
#include "State/GameState.h"

/* Program Defined */
#include "State/StateStack.h"
#include "Utility/Context.h"

/* Standard Library */
#include <fstream>
#include <stdexcept>

/* JSON Library */
#include "nlohmann/json.hpp"

namespace States {
  GameState::GameState(const bool newGame)
    : State()
    , m_stageFactory(newGame, m_pContext->getQuickSave())
  {
    setType(StateType::Game);
    m_pContext->setScore(0);

    if (!newGame && !m_pContext->getQuickSave()) {
      try {
        loadStageData();
      } catch (const std::runtime_error& error) {
        std::cerr << error.what() << std::endl;
      }
    } else if (newGame) {
      m_pContext->setQuickSave(false);
    }
      
    m_pStage = m_stageFactory.createStage(this, m_pContext->getStage(), m_pContext->getMultiplayer(), m_pContext->getQuickSave());
  }

  GameState::~GameState() {
    delete m_pStage;
    m_pStage = NULL;
  }

  void GameState::keyPressed(sf::Keyboard::Key key) {
    switch (key) {
      case (sf::Keyboard::Escape):
        m_pStateStack->pushState(StateType::Pause, static_cast<State*>(this));
        setPaused(true);
        break;
      default:
        break;
    }
  }

  void GameState::lostFocus() {
    m_pStateStack->pushState(StateType::Pause, static_cast<State*>(this));
    setPaused(true);
  }

  void GameState::setPaused(const bool paused) {
    m_pStage->setPaused(paused);
  }

  void GameState::saveGame() {
    nlohmann::ordered_json stageJSON;

    stageJSON["stageID"] = m_pContext->getStage();
    stageJSON["size"] = { {"x", m_pGraphicsManager->getStageSize().x}, {"y", m_pGraphicsManager->getStageSize().y} };
    stageJSON["multiplayer"] = m_pContext->getMultiplayer();
    stageJSON["quickSave"] = m_pContext->getQuickSave();
    std::ofstream stageData("saves/stage.json");

    stageData << std::setw(2) << stageJSON;
    stageData.close();

    m_pStage->saveGame();
  }

  void GameState::loadStageData() {
    using namespace nlohmann;

    std::ifstream stageStream("saves/stage.json");
    if (!stageStream)
      throw std::runtime_error("Error loading stage data!");
      
    ordered_json stageData = ordered_json::parse(stageStream);
    m_pContext->setStage(stageData["stageID"].template get<Stages::ID>());
    m_pGraphicsManager->setStageSize(stageData["size"]["y"].template get<float>(), stageData["size"]["x"].template get<float>());
    m_pContext->setMultiplayer(stageData["multiplayer"].template get<bool>());
    m_pContext->setQuickSave(stageData["quickSave"].template get<bool>());

    stageStream.close();
  }

  void GameState::gameOver() {
    if (m_pContext->getQuickSave()) {
      m_pStateStack->pushState(StateType::Continue, NULL, true);
    } else {
      m_pStateStack->pushState(StateType::EndStage, static_cast<State*>(this));
      setPaused(true);
    }
  }

  void GameState::exec() {
    m_pStage->exec();
    m_pContext->setScore(m_pStage->getScore());
  }
}