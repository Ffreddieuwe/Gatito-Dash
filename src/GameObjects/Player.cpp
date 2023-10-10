#include "Player.h"

Player::Player() {}
Player::~Player() {}

bool Player::gemCollision(Gem gem)
{
  float gem_top = gem.getSprite()->getPosition().y;
  float gem_left = gem.getSprite()->getPosition().x;
  float gem_height = gem.getSprite()->getGlobalBounds().height;
  float gem_width = gem.getSprite()->getGlobalBounds().width;
  float gem_bottom = gem_top + gem_height;
  float gem_right = gem_left + gem_width;

  float player_height = getSprite()->getGlobalBounds().height;
  float player_width = width;
  float player_left = getSprite()->getPosition().x;
  float player_right = player_left + player_width;
  float player_top = getSprite()->getPosition().y;
  float player_bottom = player_top + player_height;
  if (flipped)
  {
    player_left -= player_width;
    player_right -= player_width;
  }

  if ((gem_right >= player_left && gem_right <= player_right) ||
      (gem_left >= player_left && gem_left <= player_right))
  {
    if ((gem_top >= player_top && gem_top <= player_bottom) ||
        (gem_bottom >= player_top && gem_bottom <= player_bottom))
    {
      return true;
    }
  }

  return false;
}


void Player::playerInit(bool in_menu)
{
  //Set animation variables to defaults
  texture_select = 0;
  frame_select = 0;
  score = 0;
  halted = false;
  OOB = false;
  flipped = true;

  //Initialise player
  initSprite(player_textures[texture_select],
                    texture_sizes[texture_select]);
  player_vector.x = 0;
  player_vector.y = 0;
  hp = 3;
  airborne = false;
  on_platform = true;

  if (in_menu)
  {
    getSprite()->setScale(10,10);
  }
  else
  {
    getSprite()->setScale(5,5);
  }

  width = getSprite()->getGlobalBounds().width;
}


void Player::runAnimation()
{
  //Checks time elapsed on animation clock before cycling through sprites
  if (clock1.getElapsedTime().asSeconds() > 0.1f)
  {
    if (texture_select != 4 || texture_sizes[texture_select].top
      < steps[texture_select][frame_select] * (frames[texture_select] - 1))
    {
      if (texture_sizes[texture_select].top
          >= (steps[texture_select][frame_select]
              *(frames[texture_select]-1)))
      {
        //Resets to first sprite on sprite sheet

        if (texture_select == 3)
        {
          if (player_vector.x != 0)
          {
            texture_select = 1;
          }
          else
          {
            texture_select = 0;
          }
        }

        texture_sizes[texture_select].top = 0;
        frame_select = 0;
      }
      else
      {
        //Moves on to next sprite in sheet
        texture_sizes[texture_select].top
          += steps[texture_select][frame_select];
        frame_select++;
      }
    }

    //Sets sprite to new texture and restarts clock

    initSprite(player_textures[texture_select],
                 texture_sizes[texture_select]);

    clock1.restart();
  }
}

void Player::landingCheck()
{
  frame_select = 0;
  if (player_vector.x != 0)
  {
    texture_sizes[texture_select].top = 0;
    texture_select = 1;
    texture_sizes[texture_select].top = 0;
  }
  else
  {
    texture_select = 0;
  }

  if (hp < 1)
  {
    texture_select = 4;
  }
}

void Player::jumpEnd(bool &key_pressed)
{
  getSprite()->setPosition(getSprite()->getPosition().x,
                                    jump_start);
  velocityY = 0;
  airborne = false;
  on_platform = true;
  key_pressed = false;
  jump_start = 1000;

  //Sets texture to correct animation when landing
  landingCheck();
}

void Player::outOfBounds(float houseX, float castleX)
{
  OOB = false;
  if (getSprite()->getPosition().x < houseX)
  {
    if (player_vector.x < 0)
    {
      OOB = true;
    }
  }
  else if (getSprite()->getPosition().x > castleX)
  {
    if (player_vector.x > 0)
    {
      OOB = true;
    }
  }
}