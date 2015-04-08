/*
** game.h for DuckHunt in /home/olivie_f/dev/DuckHunt
** 
** Made by Samuel Olivier
** Login   <olivie_f@epitech.net>
** 
** Started on  Fri Mar 27 10:30:56 2015 Samuel Olivier
** Last update Fri Mar 27 11:28:33 2015 Samuel Olivier
*/

#include "remote.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

typedef struct	s_game
{
  void		*mlx;
  void		*window;
  t_remote	*remote;
  /* 
     Ajoutez ici les informations relatives au jeux
     Ce n'est pas pour autant un sac à variables!!
     Les structures, ça structure!
  */
}		t_game;

int	game_loop(void *param);
void	game_init(t_game* game);
