/*
** remote.h for DuckHunt in /home/olivie_f/dev/DuckHunt
** 
** Made by Samuel Olivier
** Login   <olivie_f@epitech.net>
** 
** Started on  Fri Mar 27 10:31:02 2015 Samuel Olivier
** Last update Fri Mar 27 10:34:39 2015 Samuel Olivier
*/

#include <netinet/in.h>

#define DEFAULT_PORT_NUMBER 4242

typedef struct	s_remote
{
  int			server_socket;
  struct sockaddr_in	server_addr;
  int			client_socket;
  struct sockaddr_in	client_addr;
  char			*buffer;
  int			buffer_size;
}			t_remote;

t_remote	*new_remote();
void		delete_remote(t_remote* this);

int		remote_check_input(t_remote* this, float* x, float* y);
