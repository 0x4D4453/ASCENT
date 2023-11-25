#ifndef TEXTURES_H
#define TEXTURES_H

namespace Textures {
  enum ID {
    None = 0,

    Player1,
    Player2,
    OnePlayer,
    TwoPlayers,
    Goomba,
    Fly,
    Tyrant,
    Projectile,

    Platform,
    MovingPlatform,
    PlatformLeft,
    PlatformLeftB,
    PlatformRight,
    PlatformRightB,

    StagePlatform,
    StagePlatformLeft,
    StagePlatformRight,
    StageWallLeft,
    StageWallMiddle,
    StageWallRight,
    StageCeiling,
    StageCeilingLeft,
    StageCeilingRight,
    StagePilar,
    StagePilarTop,
    StagePilarBottom,

    Bridge,
    BridgeLeft,
    BridgeRight,

    // BeltLeft,
    // BeltMiddle,
    // BeltRight,

    PipeTopLeft,
    PipeTopRight,
    PipeBottomLeft,
    PipeBottomRight,
    PipeHorizontal,
    PipeVertical,
    PipeHorizontalBroken,
    PipeVerticalBroken,

    Spring,
    Spikes,
    Door,
    Flag,

    LeftArrow,
    RightArrow,
    StagePlaceholder,
    StagePlaceholder2,

    Heart,
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

  // Cave
  constexpr char STONE_PLATFORM_LEFT[] = "assets/tiles/tile_0195.png";
  constexpr char STONE_PLATFORM_MIDDLE[] = "assets/tiles/tile_0196.png";
  constexpr char STONE_PLATFORM_RIGHT[] = "assets/tiles/tile_0197.png";
  constexpr char STONE_WALL_LEFT[] = "assets/tiles/tile_0215.png";
  constexpr char STONE_WALL_MIDDLE[] = "assets/tiles/tile_0216.png";
  constexpr char STONE_WALL_RIGHT[] = "assets/tiles/tile_0217.png";
  constexpr char STONE_CEILING_LEFT[] = "assets/tiles/tile_0235.png";
  constexpr char STONE_CEILING_MIDDLE[] = "assets/tiles/tile_0236.png";
  constexpr char STONE_CEILING_RIGHT[] = "assets/tiles/tile_0237.png";
  constexpr char STONE_PILAR_TOP[] = "assets/tiles/tile_0198.png";
  constexpr char STONE_PILAR_MIDDLE[] = "assets/tiles/tile_0218.png";
  constexpr char STONE_PILAR_BOTTOM[] = "assets/tiles/tile_0238.png";

  constexpr char BRIDGE_LEFT[] = "assets/tiles/tile_0180.png";
  constexpr char BRIDGE_MIDDLE[] = "assets/tiles/tile_0181.png";
  constexpr char BRIDGE_RIGHT[] = "assets/tiles/tile_0182.png";

  // Factory
  constexpr char STRIPPED_PLATFORM_LEFT[] = "assets/tiles/tile_0190.png";
  constexpr char STRIPPED_PLATFORM_MIDDLE[] = "assets/tiles/tile_0191.png";
  constexpr char STRIPPED_PLATFORM_RIGHT[] = "assets/tiles/tile_0192.png";
  constexpr char STRIPPED_WALL_LEFT[] = "assets/tiles/tile_0210.png";
  constexpr char STRIPPED_WALL_MIDDLE[] = "assets/tiles/tile_0211.png";
  constexpr char STRIPPED_WALL_RIGHT[] = "assets/tiles/tile_0212.png";
  constexpr char STRIPPED_CEILING_LEFT[] = "assets/tiles/tile_0230.png";
  constexpr char STRIPPED_CEILING_MIDDLE[] = "assets/tiles/tile_0231.png";
  constexpr char STRIPPED_CEILING_RIGHT[] = "assets/tiles/tile_0232.png";
  constexpr char STRIPPED_PILAR_TOP[] = "assets/tiles/tile_0193.png";
  constexpr char STRIPPED_PILAR_MIDDLE[] = "assets/tiles/tile_0213.png";
  constexpr char STRIPPED_PILAR_BOTTOM[] = "assets/tiles/tile_0233.png";

  constexpr char FLOATING_STRIPPED_PLATFORM_LEFT[] = "assets/tiles/tile_0250.png";
  constexpr char FLOATING_STRIPPED_PLATFORM_MIDDLE[] = "assets/tiles/tile_0251.png";
  constexpr char FLOATING_STRIPPED_PLATFORM_RIGHT[] = "assets/tiles/tile_0252.png";

  // constexpr char BELT_LEFT[] = "assets/tiles/tile_0124.png";
  // constexpr char BELT_MIDDLE[] = "assets/tiles/tile_0125.png";
  // constexpr char BELT_RIGHT[] = "assets/tiles/tile_0126.png";

  constexpr char PIPE_TOP_LEFT[] = "assets/tiles/tile_0227.png";
  constexpr char PIPE_TOP_RIGHT[] = "assets/tiles/tile_0229.png";
  constexpr char PIPE_BOTTOM_LEFT[] = "assets/tiles/tile_0267.png";
  constexpr char PIPE_BOTTOM_RIGHT[] = "assets/tiles/tile_0269.png";
  constexpr char PIPE_HORIZONTAL[] = "assets/tiles/tile_0228.png";
  constexpr char PIPE_VERTICAL[] = "assets/tiles/tile_0247.png";
  constexpr char PIPE_HORIZONTAL_BROKEN[] = "assets/tiles/tile_0268.png";
  constexpr char PIPE_VERTICAL_BROKEN[] = "assets/tiles/tile_0249.png";

  constexpr char SPRING[] = "assets/tiles/springSpriteSheet.png";
  constexpr char STALACTITE[] = "assets/tiles/tile_0166.png";
  constexpr char GROUND_SPIKES[] = "assets/tiles/tile_0183.png";

  constexpr char GOOMBA[] = "assets/tiles/goombaSpriteSheet.png";
  constexpr char FLY[] = "assets/tiles/flySpriteSheet.png";
  constexpr char FLY_FACTORY[] = "assets/tiles/flyFactorySpriteSheet.png";
  constexpr char TYRANT[] = "assets/tiles/bossSpriteSheet.png";

  constexpr char PROJECTILE[] = "assets/tiles/tile_0001.png";

  constexpr char LEFT_ARROW[] = "assets/tiles/leftArrow.png";
  constexpr char RIGHT_ARROW[] = "assets/tiles/rightArrow.png";
  constexpr char STAGE_PLACEHOLDER[] = "assets/stagePlaceholder.png";
  constexpr char STAGE_PLACEHOLDER2[] = "assets/stagePlaceholder2.png";

  constexpr char MOVING_PLATFORM[] = "assets/tiles/movingPlatform.png";
  constexpr char MOVING_PLATFORM_DIRT[] = "assets/tiles/dirtMovingPlatform.png";
  constexpr char DOOR[] = "assets/tiles/tile_0059.png";
  constexpr char FLAG[] = "assets/tiles/flag.png";
  
  // UI 
  constexpr char HEART[] = "assets/tiles/heartSpriteSheet.png";
}

#endif