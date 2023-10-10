#include "Game.h"
#include <iostream>

Game::Game(sf::RenderWindow& game_window)
  : window(game_window)
{
  srand(time(NULL));
}

Game::~Game()
{

}

bool Game::init()
{
  //Set game state
  current_state = Menu;

  //Run function that sets up new round
  newRound();

  audio_controller.init_sound();

  //Initialise background
  background.initObject("Data/Images/lvl1.png");
  background.texture.setRepeated(true);
  background.getSprite()->setTextureRect(sf::IntRect(0,0,
                                                     10000,1440));

  //Initialise Text
  text_controller.init_text(window.getSize().x/2);


  //Initialise buttons
  play_button.initObject("Data/Images/Buttons/Large Buttons/Play Button.png");
  play_button.getSprite()->setScale(0.3,0.3);
  float temp_x = window.getSize().x/2 -play_button.getSprite()->getGlobalBounds().width/2;
  play_button.getSprite()->setPosition(temp_x,
                                       180);

  menu_button.initObject("Data/Images/Buttons/Large Buttons/Menu Button.png");
  menu_button.getSprite()->setScale(0.3,0.3);
  menu_button.getSprite()->setPosition(temp_x,
                                       180);

  exit_button.initObject("Data/Images/Buttons/Large Buttons/Exit Button.png");
  exit_button.getSprite()->setScale(0.3,0.3);
  exit_button.getSprite()->setPosition(temp_x,
                                       300);

  ground_level = window.getSize().y-10;
  map.create();


  return true;
}

void Game::newRound()
{
  //Set click/key handling variables
  pressed = None;
  key_pressed = false;

  //Initialise enemy
  enemy.enemyInit();
  enemy.getSprite()->setPosition(4200,window.getSize().y
                                        - (enemy.getSprite()->getGlobalBounds().height+25));


  //Initialise spike
  for (int x = 0; x<4; x++)
  {
    spikes[x].initSpike(x);
  }

  // Initialise Player
  if (current_state==Menu)
  {
    player.playerInit(true);
    player.getSprite()->setPosition((window.getSize().x/2)-
                                      (player.getSprite()->getGlobalBounds().width/2),
                                    window.getSize().y-
                                      (player.getSprite()->getGlobalBounds().height+10));
  }
  else
  {
    player.playerInit(false);
    player.getSprite()->setPosition(window.getSize().x,
                                    window.getSize().y
                                      -(player.getSprite()->getGlobalBounds().height+25));
  }


  //Sets up view
  player_view.setCenter(player.getSprite()->getPosition().x +
                          (player.getSprite()->getGlobalBounds().width/2),
                        window.getSize().y/2);
  player_view.setSize(window.getSize().x,window.getSize().y);
  window.setView(player_view);


  //Sets up life counter
  life_counter = 0;
  for (int x=0; x<player.hp; x++)
  {
    life_counter++;
    lives[x].initObject("Data/Images/heart.png");
    lives[x].getSprite()->setScale(0.1,0.1);
    lives[x].getSprite()->setPosition(window.getSize().x/2+50+(x*30) +
                                        (player.getSprite()->getGlobalBounds().width/2),
                                      10);
    lives[x].is_visible = true;
  }

  //Sets up gems
  gem_counter = 5;
  for (int x=0; x<5; x++)
  {
    gems[x].gem_init(x);
  }

  //Sets up pause/play button
  pause_play_button.initObject("Data/Images/Buttons/Pause Square Button.png");
  pause_play_button.getSprite()->setScale(0.2,0.2);
  pause_play_button.getSprite()->setPosition(window.getSize().x/2 +
                                               (player.getSprite()->getGlobalBounds().width/2),
                                             0);

  //Sets up house object
  house.initObject("Data/Images/house.png");
  house.getSprite()->setScale(0.5,0.5);
  house.getSprite()->setPosition(player.getSprite()->getPosition().x
                                   - (house.getSprite()->getGlobalBounds().width
                                      *1.5),
                                 window.getSize().y
                                   -(house.getSprite()->getGlobalBounds().height));

  //Sets up castle object
  castle.initObject("Data/Images/castle.png");
  castle.getSprite()->setScale(0.8,0.8);
  castle.getSprite()->setPosition(player.getSprite()->getPosition().x
                                     + (castle.getSprite()->getGlobalBounds().width*5),
                                   window.getSize().y
                                     -(castle.getSprite()->getGlobalBounds().height - 35));

  for (int x=0; x<8; x++)
  {
    platforms[x].initObject("Data/Images/kenney_physicspack/PNG/Wood elements/elementWood011.png");
    platforms[x].positionSet(x);
    platforms[x].player_on = false;
  }
}

void Game::resetButtons()
{
  float temp_val = 0;
  if (player.getSprite()->getScale().x > 0)
  {
    temp_val = player.getSprite()->getGlobalBounds().width/2;
  }
  else
  {
    temp_val = player.getSprite()->getGlobalBounds().width +
               (player.getSprite()->getGlobalBounds().width/2);
  }

  menu_button.getSprite()->setPosition(player.getSprite()->getPosition().x
                                         - (temp_val),180);

  exit_button.getSprite()->setPosition(player.getSprite()->getPosition().x
                                         - (temp_val),300);

  text_controller.pause_text.setPosition(player.getSprite()->getPosition().x
                                         - (temp_val+3),90);

  text_controller.game_over_text.setPosition(player.getSprite()->getPosition().x
                                           - (temp_val),50);

  text_controller.game_won_text.setPosition(player.getSprite()->getPosition().x
                                           - (temp_val),50);
}


void Game::update(float dt)
{
  if (current_state == Menu)
  {
    player.runAnimation();
  }
  else if (current_state == Gameplay)
  {
    if (gem_counter == 0 && player.getSprite()->getPosition().x
                              > castle.getSprite()->getPosition().x + 150)
    {
      current_state = End_Screen;
      resetButtons();
    }
    else if (life_counter == 0)
    {
      current_state = End_Screen;
      resetButtons();
    }

    //Runs animations
    enemy.runAnimation();
    enemy.Patrol(dt);
    if (enemy.playerCollision(player))
    {
      if (dmg_clock.getElapsedTime().asSeconds() > 1)
      {
        audio_controller.hit_sound.play();
        dmg_clock.restart();
        player.texture_select = 3;
        player.frame_select   = 0;
        life_counter--;
        player.hp--;

        if (life_counter < 1)
        {
          player.texture_select = 4;
          player.frame_select   = 0;
        }
      }
    }

    for (int x = 0; x<4; x++)
    {
      if (spikes[x].playerCollision(player))
      {
        if (dmg_clock.getElapsedTime().asSeconds() > 1)
        {
          audio_controller.hit_sound.play();
          dmg_clock.restart();
          player.texture_select = 3;
          player.frame_select   = 0;
          life_counter--;
          player.hp--;

          if (life_counter < 1)
          {
            player.texture_select = 4;
            player.frame_select   = 0;
          }
        }
      }
    }

    player.runAnimation();

    //Gem code
    for (int x=0; x<5; x++)
    {
      if (gems[x].is_visible)
      {
        gems[x].bounceFunction(x,dt);

        if (player.gemCollision(gems[x]) && !gems[x].fading)
        {
          audio_controller.coin_sound.play();
          gems[x].fading = true;
          gem_counter -= 1;
          player.score++;
          text_controller.score_text.setString(std::to_string(player.score));
        }

        if (gems[x].fading)
        {
          gems[x].fade_out();
        }
      }
    }

    //Jump handling
    if (player.airborne || !player.on_platform)
    {
      player.velocityY+=gravity*dt*70;

      if(player.getSprite()->getPosition().y>player.jump_start)
      {
        player.jumpEnd(key_pressed);
      }

      player.getSprite()->move(0, player.velocityY*dt*50);
    }


    //Checks whether sprite has gone out of bounds or has hit the side of a box
    player.halted = false;
    for (int x=0; x<8; x++)
    {
      platforms[x].playerCollision(player, key_pressed, ground_level);
    }

    player.outOfBounds(house.getSprite()->getPosition().x
                       + (house.getSprite()->getGlobalBounds().width),
                       castle.getSprite()->getPosition().x +
                         (castle.getSprite()->getGlobalBounds().width));

    if (!player.halted && !player.OOB)
    {
      //Moves player, camera and ui objects
      player.getSprite()->move(player.player_vector.x*dt*250,0);
      player_view.move(player.player_vector.x*dt*250,0);
      window.setView(player_view);
      pause_play_button.getSprite()->move(player.player_vector.x*dt*250,0);
      text_controller.score_text.move(player.player_vector.x*dt*250,0);
      for (int x=0; x<player.hp; x++)
      {
        lives[x].getSprite()->move(player.player_vector.x*dt*250,
                                   0);
      }
    }
  }
  else if (current_state == End_Screen)
  {
    if (player.airborne || !player.on_platform)
    {
      player.velocityY+=gravity*dt*70;

      if(player.getSprite()->getPosition().y>player.jump_start)
      {
        player.jumpEnd(key_pressed);
      }
      player.getSprite()->move(0, player.velocityY*dt*50);
    }

    if (player.texture_select == 1)
    {
      player.texture_select = 0;
    }
    player.runAnimation();
  }
}

void Game::render()
{
  window.draw(*background.getSprite());
  if (current_state == Menu)
  {
    window.draw(*player.getSprite());
    window.draw(text_controller.menu_text);
    window.draw(*play_button.getSprite());
    window.draw(*exit_button.getSprite());
  }
  else if (current_state == Gameplay)
  {
    window.draw(*house.getSprite());
    window.draw(*castle.getSprite());
    for (int x = 0; x<4; x++)
    {
      window.draw(*spikes[x].getSprite());
    }
    window.draw(map);
    for (int x=0; x<player.hp; x++)
    {
      if (lives[x].is_visible)
      {
        window.draw(*lives[x].getSprite());
      }
    }
    for (int x=0; x<8; x++)
    {
      window.draw(*platforms[x].getSprite());
    }
    window.draw(text_controller.control_tutorial);
    window.draw(text_controller.obstacle_tutorial);
    window.draw(*enemy.getSprite());
    for (int x=0; x<5; x++)
    {
      if (gems[x].is_visible)
      {
        window.draw(*gems[x].getSprite());
      }
    }
    window.draw(*player.getSprite());
    window.draw(*pause_play_button.getSprite());
    window.draw(text_controller.score_text);
  }
  else if (current_state == Pause)
  {
    window.draw(*house.getSprite());
    window.draw(*castle.getSprite());
    for (int x = 0; x<4; x++)
    {
      window.draw(*spikes[x].getSprite());
    }
    window.draw(map);
    for (int x=0; x<player.hp; x++)
    {
      if (lives[x].is_visible)
      {
        window.draw(*lives[x].getSprite());
      }
    }
    for (int x=0; x<8; x++)
    {
      window.draw(*platforms[x].getSprite());
    }
    window.draw(text_controller.pause_text);
    window.draw(*enemy.getSprite());
    for (int x=0; x<5; x++)
    {
      if (gems[x].is_visible)
      {
        window.draw(*gems[x].getSprite());
      }
    }
    window.draw(*player.getSprite());
    window.draw(*pause_play_button.getSprite());
    window.draw(*exit_button.getSprite());
    window.draw(*menu_button.getSprite());
    window.draw(text_controller.score_text);
  }
  else if (current_state == End_Screen)
  {
    window.draw(*castle.getSprite());
    window.draw(map);
    window.draw(*player.getSprite());
    window.draw(*exit_button.getSprite());
    window.draw(*menu_button.getSprite());
    window.draw(text_controller.score_text);
    if (life_counter < 1)
    {
      window.draw(text_controller.game_over_text);
    }
    else
    {
      window.draw(text_controller.game_won_text);
    }
  }
}

void Game::mouseClicked(sf::Event event)
{
  //get the click position
  sf::Vector2i pixel_click = sf::Mouse::getPosition(window);
  sf::Vector2f click = window.mapPixelToCoords(pixel_click);

  //Click handling for buttons
  if (current_state == Menu)
  {
    if (play_button.isInside(click))
    {
      audio_controller.click_sound.play();
      play_button.initObject("Data/Images/Buttons/Colored Large Buttons/Play col_Button.png");
      pressed = Play_but;
    }
    else if (exit_button.isInside(click))
    {
      audio_controller.click_sound.play();
      exit_button.initObject("Data/Images/Buttons/Colored Large Buttons/Exit  col_Button.png");
      pressed = Exit_but;
      //audio_controller.pipe_sound.play();
    }
  }
  else if (current_state == Gameplay)
  {
    if (pause_play_button.isInside(click))
    {
      audio_controller.click_sound.play();
      pause_play_button.initObject("Data/Images/Buttons/Pause col_Square Button.png");
      pressed = Pause_Play_but;
    }
  }
  else if (current_state == Pause)
  {
    if (exit_button.isInside(click))
    {
      audio_controller.click_sound.play();
      exit_button.initObject("Data/Images/Buttons/Colored Large Buttons/Exit  col_Button.png");
      pressed = Exit_but;
      //audio_controller.pipe_sound.play();
    }
    else if (pause_play_button.isInside(click))
    {
      pause_play_button.initObject("Data/Images/Buttons/Play col_Square Button.png");
      pressed = Pause_Play_but;
    }
    else if (menu_button.isInside(click))
    {
      audio_controller.click_sound.play();
      menu_button.initObject("Data/Images/Buttons/Colored Large Buttons/Menu  col_Button.png");
      pressed = Menu_but;
    }
  }
  else if (current_state == End_Screen)
  {
    if (menu_button.isInside(click))
    {
      audio_controller.click_sound.play();
      menu_button.initObject("Data/Images/Buttons/Colored Large Buttons/Menu  col_Button.png");
      pressed = Menu_but;
    }
    else if (exit_button.isInside(click))
    {
      audio_controller.click_sound.play();
      exit_button.initObject("Data/Images/Buttons/Colored Large Buttons/Exit  col_Button.png");
      pressed = Exit_but;
      //audio_controller.pipe_sound.play();
    }
  }
}

void Game::mouseReleased(sf::Event event)
{
  //get the click position
  sf::Vector2i click = sf::Mouse::getPosition(window);

  //Click handling for buttons
  if (current_state == Menu)
  {
    if (pressed == Play_but)
    {
      play_button.initObject("Data/Images/Buttons/Large Buttons/Play Button.png");
      current_state = Gameplay;
      newRound();
    }
    else if (pressed == Exit_but)
    {
      exit_button.initObject("Data/Images/Buttons/Large Buttons/Exit Button.png");
      window.close();
    }
  }
  else if (current_state == Gameplay)
  {
    if (pressed == Pause_Play_but)
    {
      pause_play_button.initObject("Data/Images/Buttons/Play Square Button.png");
      current_state = Pause;
      audio_controller.music.setVolume(35);
      resetButtons();
    }
  }
  else if (current_state == Pause)
  {
    if (pressed == Pause_Play_but)
    {
      pause_play_button.initObject("Data/Images/Buttons/Pause Square Button.png");
      current_state = Gameplay;
      audio_controller.music.setVolume(75);
    }
    else if (pressed == Exit_but)
    {
      exit_button.initObject("Data/Images/Buttons/Large Buttons/Exit Button.png");
      window.close();
    }
    else if (pressed == Menu_but)
    {
      menu_button.initObject("Data/Images/Buttons/Large Buttons/Menu Button.png");
      current_state = Menu;
      init();
    }
  }
  else if (current_state == End_Screen)
  {
    if (pressed == Exit_but)
    {
      exit_button.initObject("Data/Images/Buttons/Large Buttons/Exit Button.png");
      window.close();
    }
    else if (pressed == Menu_but)
    {
      menu_button.initObject("Data/Images/Buttons/Large Buttons/Menu Button.png");
      current_state = Menu;
      init();
    }
  }
  pressed = None;
}

void Game::keyPressed(sf::Event event)
{
  if (current_state == Gameplay)
  {
    if (!key_pressed)
    {
      if (event.key.code == sf::Keyboard::D)
      {
        if (player.texture_select != 3)
        {
          player.flipped = false;
          player.player_vector.x = 2;
          player.player_vector.normalise();
          player.texture_sizes[player.texture_select].top = 0;
          player.frame_select = 0;
          player.texture_select = 1;
          player.texture_sizes[player.texture_select].top = 0;
          if (player.getSprite()->getScale().x<0)
          {
            player.getSprite()->move(-player.getSprite()->getGlobalBounds().width,
                                     0);
          }
          player.getSprite()->setScale(5,5);
        }
      }
      else if (event.key.code == sf::Keyboard::A)
      {
        if (player.texture_select != 3)
        {
          player.flipped = true;
          player.player_vector.x = -2;
          player.player_vector.normalise();
          player.texture_sizes[player.texture_select].top = 0;
          player.frame_select = 0;
          player.texture_select = 1;
          player.texture_sizes[player.texture_select].top = 0;
          if (player.getSprite()->getScale().x>0)
          {
            player.getSprite()->move(player.getSprite()->getGlobalBounds().width,
                                     0);
          }
          player.getSprite()->setScale(-5,5);
        }
      }
    }
    if (event.key.code == sf::Keyboard::Space && !player.airborne)
    {
      if (player.texture_select != 3)
      {
        audio_controller.jump_sound.play();
        player.texture_sizes[player.texture_select].top = 0;
        player.frame_select = 0;
        player.texture_select = 2;
        player.texture_sizes[player.texture_select].top = 0;

        player.airborne = true;
        player.velocityY = -12;

        player.jump_start = player.getSprite()->getPosition().y;
      }
    }
    key_pressed = true;
  }
}

void Game::keyReleased(sf::Event event)
{
  if (current_state == Gameplay)
  {
    key_pressed = false;
    if (event.key.code == sf::Keyboard::D)
    {
      player.player_vector.x = 0;
      if (!player.airborne)
      {
        if (player.texture_select != 3)
        {
          player.texture_select = 0;
        }
      }
    }
    else if (event.key.code == sf::Keyboard::A)
    {
      player.player_vector.x = 0;
      if (!player.airborne)
      {
        if (player.texture_select != 3)
        {
          player.texture_select = 0;
        }
      }
    }
    if (event.key.code == sf::Keyboard::Space)
    {
      if(player.velocityY < -6)
      {
        player.velocityY = -6;
      }
    }
  }
  else if (current_state == Pause)
  {
    key_pressed = false;
    if (event.key.code == sf::Keyboard::D)
    {
      player.player_vector.x = 0;
      player.texture_select = 0;
    }
    else if (event.key.code == sf::Keyboard::A)
    {
      player.player_vector.x = 0;
      player.texture_select = 0;
    }
  }
}