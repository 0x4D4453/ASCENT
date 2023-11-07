#ifndef GRAPHICSMANAGER_H
#define GRAPHICSMANAGER_H

/* SFML Library */
#include <SFML/Graphics.hpp>
#include <SFML/System/NonCopyable.hpp>

/* Forward Declaration */
class Being;
namespace States { class StateStack; }

namespace Manager {
  class GraphicsManager : sf::NonCopyable {
    private:
      static GraphicsManager* m_instance;
      sf::RenderWindow m_window;
      sf::View m_view;
      sf::Event m_event;
      States::StateStack* m_pStateStack;
      const sf::Time m_timePerFrame;
      sf::Time m_timeSinceLastUpdate;
    
    private:
      GraphicsManager();
      void windowSetup();
    
    public:
      ~GraphicsManager();
      static GraphicsManager* getInstance();

      /* Window Methods */
      const bool isOpen() const;
      void pollEvents();
      void clear();
      void display();
      void close();
      sf::RenderWindow* getWindow();
      void drawBeing(Being* pBeing);

      /* View Methods */
      void setView();
      void setViewCenter(float x, float y);
      void resetView();
      const sf::Vector2f getViewSize() const;
      const sf::Vector2f getViewCenter() const;
      const sf::Vector2f getViewCoordinates() const;

      /* Fixed Time Step */
      const sf::Time* getTimePerFrame() const;
      sf::Time* getTimeSinceLastUpdate();
      void addTime(const sf::Time& time);
  };
}

#endif