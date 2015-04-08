/*
** game.c for DuckHunt in /home/olivie_f/dev/DuckHunt
** 
** Made by Samuel Olivier
** Login   <olivie_f@epitech.net>
** 
** Started on  Fri Mar 27 10:30:37 2015 Samuel Olivier
** Last update Fri Mar 27 11:29:17 2015 Samuel Olivier
*/

#include "game.h"

#include <stdio.h>
#include <mlx.h>

static void	game_update(t_game* game)
{
  float		x;
  float		y;

  if (remote_check_input(game->remote, &x, &y)) {
    /*
      Ici l'utilisateur a cliqué sur son écran
      x et y sont des valeurs entre 0 et 1
      0 correspond à la coordonnée 0 en pixels
      1 correspond respextivement à WINDOW_WIDTH et WINDOW_HEIGHT en pixel
    */
    printf("Input %f:%f\n", x, y);
  }
}

static void	game_draw(t_game* game)
{
  (void)game;
  /*
    Fonction pour dessiner le jeu
  */
}

int		game_loop(void *param)
{
  t_game	*game;

  game = (t_game*)param;
  game_update(game);
  game_draw(game);
  return (0);
}

void	game_init(t_game* game)
{
  game->mlx = mlx_init();
  game->window = mlx_new_window(game->mlx, WINDOW_WIDTH, WINDOW_HEIGHT,
				"Duck Hunt");

  /*
    Ajoutez ici l'initialisation des attributs perso de t_game 
  */
}
