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
    
    private:
      GraphicsManager();
      void windowSetup();
    
    public:
      ~GraphicsManager();
      static GraphicsManager* getInstance();
      const bool isOpen() const;
      void pollEvents();
      void clear();
      void display();
      void close();
      void drawBeing(Being* pBeing);
      void setView();
      void setViewCenter(float x, float y);
      void resetView();
      const sf::Vector2f getViewSize() const;
      const sf::Vector2f getViewCenter() const;
      const sf::Vector2f getViewCoordinates() const;
      sf::RenderWindow* getWindow();
  };
}

#endif