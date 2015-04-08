/*
** main.c for DuckHunt in /home/olivie_f/dev/DuckHunt
** 
** Made by Samuel Olivier
** Login   <olivie_f@epitech.net>
** 
** Started on  Fri Mar 27 10:30:45 2015 Samuel Olivier
** Last update Fri Mar 27 11:29:09 2015 Samuel Olivier
*/

#include <mlx.h>
#include <stdlib.h>

#include "game.h"

int		main()
{
  t_game	game;

  game.remote = new_remote();
  if (game.remote == NULL) {
    return (1);
  }
  game_init(&game);
  mlx_loop_hook(game.mlx, &game_loop, &game);
  /*
    Vous pouvez appeler d'autre fonctions mlx_*_hook() ici
  */
  mlx_loop(game.mlx);
  return (0);
}
