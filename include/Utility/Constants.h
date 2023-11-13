#ifndef CONSTANTS_H
#define CONSTANTS_H

namespace Constants {
  constexpr unsigned int WINDOW_WIDTH = 1280;
  constexpr unsigned int WINDOW_HEIGHT = 640;
  constexpr char GAME_NAME[] = "GOTY";
  constexpr int WINDOW_STYLE = sf::Style::Close | sf::Style::Titlebar;
  constexpr float FIXED_STEP = 1.f/120.f;

  constexpr float SCALE = 2.f;
  constexpr float SPRITE_SIZE = 16.f;
  constexpr float TILE_SIZE = SPRITE_SIZE * SCALE;
  
  constexpr float GRAVITY = 20.f;
  constexpr float DRAG = 1.5f;
  constexpr float MAX_FALL_SPEED = 20.f;
}

#endif