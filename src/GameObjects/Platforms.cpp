#include "Platforms.h"

void Platforms::enemyCollision(Enemy& enemy)
{

}

void Platforms::playerCollision(Player& player, bool& key_pressed, float ground_level)
{
  float player_height = player.getSprite()->getGlobalBounds().height;
  float player_width = player.width;
  float player_left = player.getSprite()->getPosition().x;
  float player_right = player_left + player_width;
  float player_top = player.getSprite()->getPosition().y;
  float player_bottom = player_top + player_height;
  float player_middle_v = player_top + (player_height/2);
  if (player.flipped)
  {
    player_left -= player_width;
    player_right -= player_width;
  }

  float platform_height = getSprite()->getGlobalBounds().height;
  float platform_width = getSprite()->getGlobalBounds().width;
  float platform_top = getSprite()->getPosition().y;
  float platform_left = getSprite()->getPosition().x;
  float platform_bottom = platform_top + platform_height;
  float platform_right = platform_left + platform_width;



  if (player_right -10 > platform_left &&
      player_left + 10 < platform_right)
  {

    if (platform_bottom-10 < player_top && player_top < platform_bottom)
    {
      player.getSprite()->setPosition(player.getSprite()->getPosition().x,
                                      platform_bottom);
      player.velocityY = 6;
      player.jump_start = ground_level - (player_height+5);
      return;
    }
    else if ((player_top < platform_bottom && player_top > platform_top) ||
             (player_bottom < platform_bottom
         && player_bottom > platform_top+10) ||
        (player_middle_v < platform_bottom && player_middle_v
                                                > platform_top))
    {
      //player.halted = true;
      if (player_left > platform_left)
      {
        if (player.player_vector.x < 0)
        {
          player.halted = true;
        }
      }
      else if (player_right < platform_right)
      {
        if (player.player_vector.x > 0)
        {
          player.halted = true;
        }
      }
      return ;
    }
    else if (player_bottom < platform_top && player_bottom > platform_top - 15)
    {
      if (player_right - 15 > platform_left &&
        player_left + 15 < platform_right)
      {
        if (player.airborne && player.velocityY > 0)
        {
          player.jumpEnd(key_pressed);
          player.getSprite()->setPosition(player.getSprite()->getPosition().x,
                                          platform_top - (player_height-10));
          player_on = true;
          return;
        }
      }
    }
    return ;
  }
  else if (player_on)
  {
    player_on = false;
    player.on_platform = false;
    player.airborne = true;
    if (player.velocityY == 0)
    {
      player.velocityY = 6;
    }
    player.jump_start = ground_level - (player_height+5);
  }
}


void Platforms::positionSet(int platform_number)
{
  getSprite()->setPosition(positions[platform_number][0],
                           positions[platform_number][1]);
}
