#ifndef SOUNDS_H
#define SOUNDS_H

namespace Sounds {
  enum ID {
    playerJump,
    menuSound,
    Coin,
    Save,
    Pause
  };

  constexpr char MENU[] = "assets/sfx/menuSound.wav";
  constexpr char PLAYER_JUMP[] = "assets/sfx/jumpSound.ogg";
  constexpr char CAVE_BG[] = "assets/music/underground.flac";
  constexpr char FACTORY_BG[] = "assets/music/dungeon.flac";
  constexpr char PAUSE[] = "assets/sfx/smw_pause.wav";
  constexpr char SAVE[] = "assets/sfx/smw_save_menu.wav";
  constexpr char COIN[] = "assets/sfx/smw_coin.wav";
}

#endif