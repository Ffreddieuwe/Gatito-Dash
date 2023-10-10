#include "Audio.h"

void Audio::init_sound()
{
  music.openFromFile("Data/Audio/music_zapsplat_easy_cheesy.wav");
  music.play();
  music.setVolume(75);

  hit_buffer.loadFromFile("Data/Audio/hitHurt.wav");
  hit_sound.setBuffer(hit_buffer);

  jump_buffer.loadFromFile("Data/Audio/jump.wav");
  jump_sound.setBuffer(jump_buffer);

  click_buffer.loadFromFile("Data/Audio/click.wav");
  click_sound.setBuffer(click_buffer);

  coin_buffer.loadFromFile("Data/Audio/pickupCoin.wav");
  coin_sound.setBuffer(coin_buffer);

  pipe_buffer.loadFromFile("Data/Audio/pipe.wav");
  pipe_sound.setBuffer(pipe_buffer);
}
