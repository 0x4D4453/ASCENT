/* Main Include */
#include "Manager/GraphicsManager.h"

/* Program Defined */
#include "Being.h"
#include "State/StateStack.h"
#include "Utility/Constants.h"

/* SFML Library */
#include <SFML/Graphics.hpp>

namespace Manager {
  GraphicsManager* GraphicsManager::m_instance(NULL);

  GraphicsManager::GraphicsManager()
    : m_window(sf::VideoMode(Constants::WINDOW_WIDTH, Constants::WINDOW_HEIGHT), Constants::GAME_NAME, Constants::WINDOW_STYLE)
    , m_view(sf::Vector2f(0.f, 0.f), sf::Vector2f(static_cast<float>(Constants::WINDOW_WIDTH), static_cast<float>(Constants::WINDOW_HEIGHT)))
    , m_pStateStack(States::StateStack::getInstance())
    , m_timePerFrame(sf::seconds(Constants::FIXED_STEP))
    , m_timeSinceLastUpdate(sf::Time::Zero)
  {
    
  }

  void GraphicsManager::windowSetup() {
    m_window.setFramerateLimit(60);
    m_window.setVerticalSyncEnabled(true);
    m_window.setMouseCursorVisible(false);
  }

  GraphicsManager::~GraphicsManager() {

  }

  GraphicsManager* GraphicsManager::getInstance() {
    if (m_instance == NULL)
      m_instance = new GraphicsManager;
    return m_instance;
  } 

  const bool GraphicsManager::isOpen() const {
    return m_window.isOpen();
  }

  void GraphicsManager::pollEvents() {
    while (m_window.pollEvent(m_event)) {
      if (m_event.type == sf::Event::Closed)
        m_window.close();
      else 
        m_pStateStack->handleEvents(m_event);
    }
  }

  void GraphicsManager::clear() {
    m_window.clear();
  }

  void GraphicsManager::display() {
    m_window.display();
  }

  void GraphicsManager::close() {
    m_window.close();
  }
  
  sf::RenderWindow* GraphicsManager::getWindow() {
    return &m_window;
  }

  void GraphicsManager::drawBeing(Being* pBeing) {
    m_window.draw(*(pBeing->getSprite()));
  }

  void GraphicsManager::setView() {
    m_window.setView(m_view);
  }

  void GraphicsManager::setViewCenter(float x, float y) {
    m_view.setCenter(sf::Vector2f(x, y));
  }

  void GraphicsManager::resetView() {
    m_window.setView(m_window.getDefaultView());
  }

  const sf::Vector2f GraphicsManager::getViewSize() const {
    return m_view.getSize();
  }

  const sf::Vector2f GraphicsManager::getViewCenter() const {
    return m_view.getCenter();
  }

  const sf::Vector2f GraphicsManager::getViewCoordinates() const {
    sf::Vector2f coordinates;
    coordinates.x = m_view.getCenter().x - m_view.getSize().x/2;
    coordinates.y = m_view.getCenter().y - m_view.getSize().y/2;
    return coordinates;
  }

  const sf::Time* GraphicsManager::getTimePerFrame() const {
    return &m_timePerFrame;
  }

  sf::Time* GraphicsManager::getTimeSinceLastUpdate() {
    return &m_timeSinceLastUpdate;
  }

  void GraphicsManager::addTime(const sf::Time& time) {
    m_timeSinceLastUpdate += time;
  }
}