/* Main Include */
#include "State/GameState.h"

/* Program Defined */
#include "State/StateStack.h"
#include "Utility/Context.h"

/* Standard Library */
#include <fstream>

/* JSON Library */
#include "nlohmann/json.hpp"

namespace States {
  GameState::GameState(const bool newGame)
    : State()
    , m_stageFactory(newGame, m_pContext->getMultiplayer())
  {
    setType(StateType::Game);

    m_pContext->setScore(0);

    if (!newGame)
      loadStageData();

    m_pStage = m_stageFactory.createStage(this, m_pContext->getStage(), m_pContext->getMultiplayer());
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
    std::ofstream stageData("saves/stage.json");

    stageData << std::setw(2) << stageJSON;
    stageData.close();

    m_pStage->saveGame();
  }

  void GameState::loadStageData() {
    using namespace nlohmann;

    std::ifstream stageStream("saves/stage.json");
    ordered_json stageData = ordered_json::parse(stageStream);

    m_pContext->setStage(stageData["stageID"].template get<Stages::ID>());
    m_pGraphicsManager->setStageSize(stageData["size"]["y"].template get<float>(), stageData["size"]["x"].template get<float>());
    m_pContext->setMultiplayer(stageData["multiplayer"].template get<bool>());

    stageStream.close();
  }

  void GameState::gameOver() {
    m_pStateStack->pushState(StateType::EndStage, static_cast<State*>(this));
    setPaused(true);
  }

  void GameState::exec() {
    m_pStage->exec();
    m_pContext->setScore(m_pStage->getScore());
  }
}