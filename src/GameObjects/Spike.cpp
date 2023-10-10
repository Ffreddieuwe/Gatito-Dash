#include "Spike.h"

bool Spike::playerCollision(Player& player)
{
  float player_top = player.getSprite()->getPosition().y;
  float player_left = player.getSprite()->getPosition().x;
  float player_height = player.getSprite()->getGlobalBounds().height;
  float player_width = player.width;
  float player_bottom = player_top + player_height;
  float player_right = player_left + player_width;
  if (player.flipped)
  {
    player_left -= player_width;
    player_right -= player_width;
  }

  float spike_height = getSprite()->getGlobalBounds().height;
  float spike_width = getSprite()->getGlobalBounds().width;
  float spike_left = getSprite()->getPosition().x;
  float spike_right = spike_left + spike_width;
  float spike_top = getSprite()->getPosition().y;
  float spike_bottom = spike_top + spike_height;


  if ((spike_right-22 >= player_left && spike_right-22 <= player_right) ||
      (spike_left+22 >= player_left && spike_left+22 <= player_right))
  {
    if ((spike_top >= player_top && spike_top <= player_bottom) ||
        (spike_bottom >= player_top && spike_bottom <= player_bottom))
    {
      return true;
    }
  }

  return false;
}

void Spike::initSpike(int num)
{
  initObject("Data/Images/Spike.png");
  getSprite()->setScale(0.08,0.08);
  getSprite()->setPosition(positions[num][0], positions[num][1]);
}
