#ifndef TEXTINPUT_H
#define TEXTINPUT_H

/* Standard Library */
#include <string>

/* SFML Library */
#include "SFML/Graphics.hpp"

namespace UI {
  class TextInput {
    private:
      sf::RectangleShape m_textBox;
      std::string m_string;
      const int m_maxStringSize;
      sf::Text m_text;
      float m_totalTime;
      bool m_showCursor;
    
    public:
      TextInput(const sf::Font& font, const sf::Vector2f position);
      ~TextInput();
      void addCharacter(char character);
      void deleteCharacter();
      std::string& getString();
      void update(const float dt);
      void draw(sf::RenderWindow& window);
      void exec(sf::RenderWindow& window, const float dt);
  };
}

#endif