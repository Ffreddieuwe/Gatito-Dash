#include "Gem.h"

Gem::Gem() {}
Gem::~Gem() {}

void Gem::gem_init(int x)
{
  initObject("Data/Images/gem.png");
  is_visible = true;
  fading = false;
  alpha = 255;
  getSprite()->setScale(0.07,0.07);
  gem_bounce = 0;
  getSprite()->setPosition(positions[x][0],positions[x][1]);
}

void Gem::bounceFunction(int gem_counter, float dt)
{
  gem_bounce++;
  if (gem_bounce>100)
  {
    gem_bounce = 0;
  }

  for (int x=0; x<gem_counter; x++)
  {
    if (gem_bounce<50)
    {
      getSprite()->move(0, 2*dt);
    }
    else if (gem_bounce>50)
    {
      getSprite()->move(0, -2*dt);
    }
  }
}

void Gem::fade_out()
{
  if (fade_clock.getElapsedTime().asSeconds() > 0.1)
  {
    alpha -= 40;
    if (alpha <= 0)
    {
      is_visible = false;
    }
    fade_clock.restart();
  }

  getSprite()->setColor(sf::Color(255,255,255,alpha));
}
