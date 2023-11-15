#ifndef TEXTURES_H
#define TEXTURES_H

namespace Textures {
  enum ID {
    Player1,
    Player2,
    OnePlayer,
    TwoPlayers,
    Goomba,
    Fly,
    Enemy3,
    Projectile,
    Platform,
    PlatformLeft,
    PlatformLeftB,
    PlatformRight,
    PlatformRightB,
    BeltLeft,
    BeltMiddle,
    BeltRight,
    StrippedPlatformLeft,
    StrippedPlatformMiddle,
    StrippedPlatformRight,
    Spikes,
  };

  constexpr char PLAYER1[] = "assets/tiles/player1SpriteSheet.png";
  constexpr char PLAYER2[] = "assets/tiles/player2SpriteSheet.png";

  constexpr char ONE_PLAYER[] = "assets/tiles/tile_0280.png";
  constexpr char TWO_PLAYERS[] = "assets/tiles/TwoPlayers.png";

  constexpr char PLATFORM[] = "assets/tiles/tile_0271.png";
  constexpr char PLATFORM_LEFT_CORNER[] = "assets/tiles/tile_0270.png";
  constexpr char PLATFORM_LEFT_CORNER_BLACK[] = "assets/tiles/tile_0290.png";
  constexpr char PLATFORM_RIGHT_CORNER[] = "assets/tiles/tile_0272.png";
  constexpr char PLATFORM_RIGHT_CORNER_BLACK[] = "assets/tiles/tile_0292.png";
  constexpr char BELT_LEFT[] = "assets/tiles/tile_0124.png";
  constexpr char BELT_MIDDLE[] = "assets/tiles/tile_0125.png";
  constexpr char BELT_RIGHT[] = "assets/tiles/tile_0126.png";
  constexpr char STRIPPED_PLATFORM_LEFT[] = "assets/tiles/tile_0190.png";
  constexpr char STRIPPED_PLATFORM_MIDDLE[] = "assets/tiles/tile_0191.png";
  constexpr char STRIPPED_PLATFORM_RIGHT[] = "assets/tiles/tile_0192.png";
  constexpr char GROUND_SPIKES[] = "assets/tiles/tile_0192.png";

  constexpr char GOOMBA[] = "assets/tiles/goombaSpriteSheet.png";
  constexpr char FLY[] = "assets/tiles/flySpriteSheet.png";
  constexpr char ENEMY1[] = "assets/tiles/tile_0320.png";
  constexpr char ENEMY2[] = "assets/tiles/tile_0340.png";
  constexpr char ENEMY3[] = "assets/tiles/tile_0122.png";

  constexpr char PROJECTILE[] = "assets/tiles/tile_0001.png";
}

#endif