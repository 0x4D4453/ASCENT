#ifndef TEXTURES_H
#define TEXTURES_H

namespace Textures {
  enum ID {
    Player1,
    Player1Walk1,
    Player1Walk2,
    Player1Walk3,
    Player1Charge,
    Player1Jump,
    Player2,
    Player2Walk1,
    Player2Walk2,
    Player2Walk3,
    Player2Charge,
    Player2Jump,
    Goomba,
    Enemy2,
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
  };

  constexpr char PLAYER1[] = "assets/tiles/tile_0240.png";
  constexpr char PLAYER1_WALK1[] = "assets/tiles/tile_0241.png";
  constexpr char PLAYER1_WALK2[] = "assets/tiles/tile_0242.png";
  constexpr char PLAYER1_WALK3[] = "assets/tiles/tile_0243.png";
  constexpr char PLAYER1_CHARGE[] = "assets/tiles/player1_charging.png";
  constexpr char PLAYER1_JUMP[] = "assets/tiles/tile_0244.png";

  constexpr char PLAYER2[] = "assets/tiles/tile_0260.png";
  constexpr char PLAYER2_WALK1[] = "assets/tiles/tile_0261.png";
  constexpr char PLAYER2_WALK2[] = "assets/tiles/tile_0262.png";
  constexpr char PLAYER2_WALK3[] = "assets/tiles/tile_0263.png";
  constexpr char PLAYER2_CHARGE[] = "assets/tiles/player2_charging.png";
  constexpr char PLAYER2_JUMP[] = "assets/tiles/tile_0264.png";

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
  constexpr char ENEMY1[] = "assets/tiles/tile_0320.png";
  constexpr char ENEMY2[] = "assets/tiles/tile_0340.png";
  constexpr char ENEMY3[] = "assets/tiles/tile_0381.png";
  constexpr char PROJECTILE[] = "assets/tiles/tile_0001.png";
}

#endif