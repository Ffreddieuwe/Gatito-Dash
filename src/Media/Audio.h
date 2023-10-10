#ifndef PLATFORMERSFML_AUDIO_H
#define PLATFORMERSFML_AUDIO_H

#include <SFML/Audio.hpp>

class Audio
{
 public:
  sf::Music music;

  sf::SoundBuffer hit_buffer;
  sf::Sound hit_sound;

  sf::SoundBuffer jump_buffer;
  sf::Sound jump_sound;

  sf::SoundBuffer click_buffer;
  sf::Sound click_sound;

  sf::SoundBuffer coin_buffer;
  sf::Sound coin_sound;

  sf::SoundBuffer pipe_buffer;
  sf::Sound pipe_sound;

  void init_sound();
};

#endif // PLATFORMERSFML_AUDIO_H
