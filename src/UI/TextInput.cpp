/* Main Include */
#include "UI/TextInput.h"

/* Program Defined */
#include "Utility/Context.h"

namespace UI {
  TextInput::TextInput(const sf::Font& font, const sf::Vector2f position)
    : m_textBox()
    , m_string("")
    , m_text(m_string, font)
    , m_maxStringSize(5)
    , m_totalTime(0)
    , m_showCursor(true)
  {
    m_textBox.setFillColor(sf::Color::Transparent);
    m_textBox.setOutlineColor(sf::Color::White);
    m_textBox.setOutlineThickness(2.f);
    m_textBox.setSize(sf::Vector2f(300.f, 50.f));

    sf::FloatRect textRect = m_textBox.getLocalBounds();
    m_textBox.setOrigin(static_cast<int>(textRect.left + textRect.width/2.0f), static_cast<int>(textRect.top + textRect.height/2.0f));
    m_textBox.setPosition(position.x, position.y);

    textRect = m_textBox.getGlobalBounds();
    m_text.setCharacterSize(50.f);
    m_text.setPosition(textRect.left + 10.f, textRect.top - 10.f);
  }

  TextInput::~TextInput() {

  }

  void TextInput::addCharacter(char character) {
    if (static_cast<int>(m_string.size()) < m_maxStringSize)
      m_string += toupper(character);
  }

  void TextInput::deleteCharacter() {
    if (static_cast<int>(m_string.size()) > 0)
      m_string.pop_back();
  }

  std::string& TextInput::getString() {
    return m_string;
  }

  void TextInput::update(const float dt) {
    m_totalTime += dt;
    if (m_totalTime >= 1.f) {
      m_showCursor = !m_showCursor;
      m_totalTime = 0.f;
    }

    char cursor = ' ';
    if (m_showCursor && static_cast<int>(m_string.size()) < m_maxStringSize)
      cursor = '_';
    
    m_text.setString(m_string + cursor);
  }

  void TextInput::draw(sf::RenderWindow& window) {
    window.draw(m_textBox);
    window.draw(m_text);
  } 

  void TextInput::exec(sf::RenderWindow& window, const float dt) {
    update(dt);
    draw(window);
  }
}