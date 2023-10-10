#include "Enemy.h"

Enemy::Enemy() {};
Enemy::~Enemy() {}

void Enemy::enemyInit()
{
  texture_select = 1;
  frame_select = 0;
  flipped = false;

  vector.y = 0;
  vector.x = 1;

  initSprite(enemy_textures[texture_select],
                   texture_sizes[texture_select]);
  getSprite()->setScale(4,4);
}

void Enemy::runAnimation()
{
  //Checks time elapsed on animation clock before cycling through sprites
  if (clock.getElapsedTime().asSeconds() > 0.1f)
  {
    if (
      texture_sizes[texture_select].top >=
      (32 * (frames[texture_select] - 1)))
    {
      // Resets to first sprite on sprite sheet
      texture_sizes[texture_select].top = 0;
      frame_select = 0;
    }
    else
    {
      // Moves on to next sprite in sheet
      texture_sizes[texture_select].top += 32;
      frame_select++;
    }

    // Sets sprite to new texture and restarts clock
    initSprite(enemy_textures[texture_select], texture_sizes[texture_select]);
    clock.restart();
  }
}

bool Enemy::playerCollision(Player player)
{
  float player_top = player.getSprite()->getPosition().y;
  float player_left = player.getSprite()->getPosition().x;
  float player_height = player.getSprite()->getGlobalBounds().height;
  float player_width = player.width;
  float player_bottom = player_top + player_height;
  float player_right = player_left + player_width;

  float enemy_height = getSprite()->getGlobalBounds().height;
  float enemy_width = getSprite()->getGlobalBounds().width;
  float enemy_left = getSprite()->getPosition().x;
  float enemy_right = enemy_left + enemy_width;
  float enemy_top = getSprite()->getPosition().y;
  float enemy_bottom = enemy_top + enemy_height;
  if (flipped)
  {
    enemy_left -= enemy_width;
    enemy_right -= enemy_width;
  }

  if ((enemy_right >= player_left && enemy_right <= player_right) ||
      (enemy_left >= player_left && enemy_left <= player_right))
  {
    if ((enemy_top >= player_top && enemy_top <= player_bottom) ||
        (enemy_bottom >= player_top && enemy_bottom <= player_bottom))
    {
      return true;
    }
  }

  return false;
}


void Enemy::Patrol(float dt)
{
  if (getSprite()->getPosition().x < patrol_start && vector.x < 0)
  {
    getSprite()->setScale(4,4);
    getSprite()->move(-getSprite()->getGlobalBounds().width,0);
    vector.x = 1;
    flipped = false;
    vector.normalise();
  }
  else if (getSprite()->getPosition().x > patrol_end && vector.x > 0)
  {
    getSprite()->setScale(-4,4);
    getSprite()->move(getSprite()->getGlobalBounds().width,0);
    vector.x = -1;
    flipped = true;
    vector.normalise();
  }

  getSprite()->move(vector.x * dt * 90, 0);
};
