#ifndef SOUNDS_H
#define SOUNDS_H

namespace Sounds {
  enum ID {
    playerJump,
    menuSound,
  };

  constexpr char MENU[] = "assets/sfx/menuSound.wav";
  constexpr char PLAYER_JUMP[] = "assets/sfx/jumpSound.ogg";
  constexpr char CAVE_BG[] = "assets/music/underground.flac";
  constexpr char FACTORY_BG[] = "assets/music/dungeon.flac";
}

#endif