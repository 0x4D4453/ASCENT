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

  constexpr char PLAYER1_TEXTURE[] = "assets/tiles/tile_0240.png";
  constexpr char PLAYER2_TEXTURE[] = "assets/tiles/tile_0260.png";
  constexpr char PLATFORM_TEXTURE[] = "assets/tiles/tile_0271.png";
  constexpr char PLATFORM_TEXTURE_LEFT_CORNER[] = "assets/tiles/tile_0270.png";
  constexpr char PLATFORM_TEXTURE_LEFT_CORNER_BLACK[] = "assets/tiles/tile_0290.png";
  constexpr char PLATFORM_TEXTURE_RIGHT_CORNER[] = "assets/tiles/tile_0272.png";
  constexpr char PLATFORM_TEXTURE_RIGHT_CORNER_BLACK[] = "assets/tiles/tile_0292.png";
  constexpr char BELT_TEXTURE_LEFT[] = "assets/tiles/tile_0124.png";
  constexpr char BELT_TEXTURE_MIDDLE[] = "assets/tiles/tile_0125.png";
  constexpr char BELT_TEXTURE_RIGHT[] = "assets/tiles/tile_0126.png";
  constexpr char STRIPPED_PLATFORM_TEXTURE_LEFT[] = "assets/tiles/tile_0190.png";
  constexpr char STRIPPED_PLATFORM_TEXTURE_MIDDLE[] = "assets/tiles/tile_0191.png";
  constexpr char STRIPPED_PLATFORM_TEXTURE_RIGHT[] = "assets/tiles/tile_0192.png";
  constexpr char ENEMY1_TEXTURE[] = "assets/tiles/tile_0320.png";
  constexpr char ENEMY2_TEXTURE[] = "assets/tiles/tile_0340.png";
  constexpr char ENEMY3_TEXTURE[] = "assets/tiles/tile_0381.png";

  constexpr float GRAVITY = 20.f;
  constexpr float MAX_FALL_SPEED = 20.f;
}

#endif