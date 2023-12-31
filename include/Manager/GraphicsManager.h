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
      sf::Clock m_clock;
      sf::View m_view;
      States::StateStack* m_pStateStack;
      const sf::Time m_timePerFrame;
      sf::Time m_timeSinceLastUpdate;
      float m_stageHeight;
      float m_stageWidth;
    
    private:
      GraphicsManager();
      void windowSetup();
    
    public:
      ~GraphicsManager();
      static GraphicsManager* getInstance();

      /* Window Methods */
      const bool isOpen() const;
      void clear();
      void display();
      void close();
      sf::RenderWindow* getWindow();
      void drawBeing(Being* pBeing);
      void draw(sf::Drawable& drawable);

      /* View Methods */
      void setView(const sf::View& view);
      void setViewCenter(float x, float y);
      void updateView(sf::View& view, float x, float y);
      void resetView();
      sf::View* getView();
      const sf::Vector2f getViewSize() const;
      const sf::Vector2f getViewCenter() const;
      const sf::Vector2f getViewCoordinates() const;

      /* Fixed Time Step */
      const sf::Time* getTimePerFrame() const;
      sf::Time* getTimeSinceLastUpdate();
      void resetTime();
      void addTime();

      void setStageSize(float height, float width);
      sf::Vector2f getStageSize();
  };
}

#endif